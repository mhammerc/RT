#include "rt.h"
#include "env.h"
#include <math.h>

// DEBUG
#include <stdio.h>
#include <string.h>

static void		opencl_check_error(cl_int error)
{
	if (error != CL_SUCCESS)
	{
		dprintf(2, "OpenCL call failed with error %d\n", error);
		exit(1);
	}
}

t_scene_manager	*opencl_get()
{
	static t_scene_manager	manager = {};

	return (&manager);
}

float			light_find_max(int w, int h, FLOAT3 *light)
{
	float		max;
	int			i;
	int			len;
	
	len = w * h;
	max = 0.;
	i = -1;
	while (++i < len)
	{
		max = fmax(max, light[i].x);
		max = fmax(max, light[i].y);
		max = fmax(max, light[i].z);
	}
	return (max);
}

int				colorcomp_to_rgb(int r, int g, int b)
{
	r = r < 0 ? 0 : (r & 0xff);
	g = g < 0 ? 0 : (g & 0xff);
	b = b < 0 ? 0 : (b & 0xff);
	return ((r << R_BITSHIFT) + (g << G_BITSHIFT) + (b << B_BITSHIFT));
}

void			light_to_pixel(FLOAT3 *light, int *px, int w, int h)
{
	float		invmax;
	int			i;
	int			len;

	len = w * h;
	invmax = 255. / light_find_max(w, h, light);
	i = -1;
	while (++i < len)
	{
		px[i] = colorcomp_to_rgb(light[i].x * invmax,
									light[i].y * invmax,
									light[i].z * invmax);
	}
	return ;
}

int				*opencl_compute_image()
{
	t_scene_manager		*manager;
	int					*pixels;
	cl_int				error;
	cl_kernel			kernel;

	//TODO: move light reduction into the kernel maybe
	FLOAT3				*light;

	//TODO: read these from interface
	t_cl_scene			*scene;
	t_obj				*obj;
	t_spot				*spot;

	scene = (t_cl_scene*)malloc(sizeof(t_cl_scene));
	scene->cam.w = 800;
	scene->cam.h = 600;
	scene->nb_obj = 1;
	scene->nb_spot = 1;
	scene->ambiant.intensity = 0.1;
	scene->ambiant.color.x = 1;
	scene->ambiant.color.y = 1;
	scene->ambiant.color.z = 1;
	scene->cam.pos.x = 0;
	scene->cam.pos.y = 0;
	scene->cam.pos.z = -10;
	scene->cam.dir.x = 0;
	scene->cam.dir.y = 0;
	scene->cam.dir.z = 0;
	scene->cam.up.x = 0;
	scene->cam.up.y = 1;
	scene->cam.up.z = 0;
	scene->cam.fov = 45;
	scene->cam.ratio = 1;
	scene->cam = camera_set(scene->cam);

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj[0].pos.x = 0;
	obj[0].pos.y = 0;
	obj[0].pos.z = 0;
	obj[0].param = 1;
	obj[0].color.x = 0.42;
	obj[0].color.y = 0.42;
	obj[0].color.z = 0;
	obj[0].kspec = 1;
	obj[0].kdiff = 1;
	obj[0].kp = 256;

	spot = (t_spot*)malloc(sizeof(t_spot));
	spot[0].pos.x = 1;
	spot[0].pos.y = 4;
	spot[0].pos.z = -4;
	spot[0].color.x = 1;
	spot[0].color.y = 1;
	spot[0].color.z = 1;
	spot[0].intensity = 1;
	//--

	pixels = (int*)malloc(sizeof(int) * scene->cam.w * scene->cam.h);
	bzero(pixels, sizeof(int) * scene->cam.w * scene->cam.h);

	light = (FLOAT3*)malloc(sizeof(FLOAT3) * scene->cam.w * scene->cam.h);
	bzero(light, sizeof(FLOAT3) * scene->cam.w * scene->cam.h);

	manager = opencl_get();
	error = CL_SUCCESS;

	cl_mem	light_buffer = clCreateBuffer(manager->context,
			CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(FLOAT3) * scene->cam.w * scene->cam.h,
			light, &error);
	opencl_check_error(error);

	cl_mem	scene_buffer = clCreateBuffer(manager->context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_cl_scene),
			scene, &error);
	opencl_check_error(error);

	cl_mem	obj_buffer = clCreateBuffer(manager->context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_obj) * scene->nb_obj,
			obj, &error);
	opencl_check_error(error);

	cl_mem	spot_buffer = clCreateBuffer(manager->context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_spot) * scene->nb_spot,
			spot, &error);
	opencl_check_error(error);

	kernel = clCreateKernel(manager->program, "compute_color", NULL);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&light_buffer);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&scene_buffer);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&obj_buffer);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&spot_buffer);
	const size_t global_work_size[] = { scene->cam.w * scene->cam.h, 0, 0 };
	opencl_check_error(clEnqueueNDRangeKernel(manager->queue, kernel, 1, NULL,
				global_work_size, NULL, 0, NULL, NULL));
	opencl_check_error(clEnqueueReadBuffer(manager->queue, light_buffer,
				CL_TRUE, 0, sizeof(FLOAT3) * scene->cam.w * scene->cam.h, light, 0, NULL, NULL));
	light_to_pixel(light, pixels, scene->cam.w, scene->cam.h);
	interface_print_scene(pixels);
	return (pixels);
}

void			opencl_init()
{
	t_scene_manager	*manager;
	cl_int			error;

	manager = opencl_get();
	error = CL_SUCCESS;
	clGetPlatformIDs(0, 0, &manager->platforms_count);
	printf("There is %u platforms.\n", manager->platforms_count);

	cl_platform_id	platforms_ids[manager->platforms_count];
	clGetPlatformIDs(manager->platforms_count, platforms_ids, 0);
	manager->platform_id = platforms_ids[0];

	clGetDeviceIDs(manager->platform_id, CL_DEVICE_TYPE_GPU, 0, 0,
			&manager->devices_count);
	printf("There is %u GPU.\n", manager->devices_count);

	manager->device_ids = (cl_device_id*)malloc(sizeof(cl_device_id) * manager->devices_count);
	clGetDeviceIDs(manager->platform_id, CL_DEVICE_TYPE_GPU, manager->devices_count,
			manager->device_ids, 0);
	manager->device_id = manager->device_ids[0];

	manager->context_properties[0] = CL_CONTEXT_PLATFORM;
	manager->context_properties[1] = (cl_context_properties)manager->platform_id;
	manager->context_properties[2] = 0;
	manager->context_properties[3] = 0;

	manager->context = clCreateContext(manager->context_properties, manager->devices_count,
			manager->device_ids, 0, 0, &error);
	opencl_check_error(error);

	manager->queue = clCreateCommandQueue(manager->context, manager->device_id, 0, &error);
	opencl_check_error(error);

	opencl_create_program(manager, (const char*[]){"./resources/kernel.cl"}, 1);
	printf("Program created.\n");

/*
** Print kernel's compilations errors
*/
	if ((error = clBuildProgram(manager->program, manager->devices_count,
					manager->device_ids, "-Iresources", NULL, NULL))
			== CL_BUILD_PROGRAM_FAILURE)
	{
		size_t	log_size;
		clGetProgramBuildInfo(manager->program, manager->device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char	*log = (char*)calloc(sizeof(char) * log_size, 0);
		clGetProgramBuildInfo(manager->program, manager->device_id,
				CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		printf("%s\n", log);
		exit(0);
	}
	opencl_check_error(error);
	printf("Program built.\n");
}

void			opencl_create_program(t_scene_manager *manager,
		const char **sources, size_t sources_count)
{
	size_t	lengths[sources_count];
	cl_int	error;
	size_t	i;

	i = 0;
	while (i < sources_count)
	{
		//DEBUG utiliser ft_strlen
		lengths[i] = strlen(sources[i]);
		++i;
	}
	error = 0;
	manager->program = clCreateProgramWithSource(manager->context, sources_count, sources, lengths,
			&error);
	opencl_check_error(error);
}
