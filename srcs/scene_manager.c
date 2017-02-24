#include "rt.h"

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

int				*opencl_compute_image()
{
	t_scene_manager		*manager;
	int					*pixels;
	size_t				max_x;
	size_t				max_y;
	cl_int				error;
	cl_kernel			kernel;

	manager = opencl_get();
	max_x = 800;
	max_y = 600;
	error = CL_SUCCESS;
	pixels = (int*)malloc(sizeof(int) * max_x * max_y);
	bzero(pixels, sizeof(int) * max_x * max_y);

	cl_mem	pixel_buffer = clCreateBuffer(manager->context,
			CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(int) * max_x * max_y,
			pixels, &error);
	opencl_check_error(error);

	kernel = clCreateKernel(manager->program, "compute_color", NULL);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&pixel_buffer);
	const size_t global_work_size[] = { max_x * max_y, 0, 0 };
	opencl_check_error(clEnqueueNDRangeKernel(manager->queue, kernel, 1, NULL,
				global_work_size, NULL, 0, NULL, NULL));
	opencl_check_error(clEnqueueReadBuffer(manager->queue, pixel_buffer,
				CL_TRUE, 0, sizeof(int) * max_x * max_y, pixels, 0, NULL, NULL));
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
