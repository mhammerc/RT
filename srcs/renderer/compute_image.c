#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "renderer.h"
#include "shared.h"

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
	return ((0xff << ALPHA_BITSHIFT) + (r << R_BITSHIFT) + (g << G_BITSHIFT) + (b << B_BITSHIFT));
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

static t_cl_scene	*scene_converter(t_scene *sce)
{
	t_cl_scene		*cl_sce;

	if (NULL == (cl_sce = (t_cl_scene*)malloc(sizeof(t_cl_scene))))
		return (NULL);
	cl_sce->nb_obj = sce->nb_obj;
	cl_sce->nb_spot = sce->nb_spot;
	cl_sce->ambiant = sce->ambiant;
	cl_sce->cam = sce->cam;
	/*
	print_camera(cl_sce->cam);
	for (int i = 0; i < sce->nb_obj; ++i)
		print_obj(sce->obj[i]);
	for (int i = 0; i < sce->nb_spot; ++i)
		print_spot(sce->light[i]);
		*/
	return (cl_sce);
}

int				*renderer_compute_image(t_scene *sce)
{
	t_scene_manager		*manager;
	int					*pixels;
	cl_int				error;
	cl_kernel			kernel;
	FLOAT3				*light;
	t_cl_scene			*scene;
	t_obj				*obj;
	t_spot				*spot;

	sce->cam = camera_set(sce->cam);
	if (NULL == (scene = scene_converter(sce)))
		return (NULL);
	obj = sce->obj;
	spot = sce->light;

	pixels = (int*)malloc(sizeof(int) * scene->cam.w * scene->cam.h);
	bzero(pixels, sizeof(int) * scene->cam.w * scene->cam.h);

	light = (FLOAT3*)malloc(sizeof(FLOAT3) * scene->cam.w * scene->cam.h);
	bzero(light, sizeof(FLOAT3) * scene->cam.w * scene->cam.h);

	manager = opencl_get();
	error = CL_SUCCESS;

	cl_mem	light_buffer = clCreateBuffer(manager->context,
			CL_MEM_READ_WRITE,
			sizeof(FLOAT3) * scene->cam.w * scene->cam.h,
			NULL, &error);
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
	cl_event e;
	opencl_check_error(clEnqueueNDRangeKernel(manager->queue, kernel, 1, NULL,
				global_work_size, NULL, 0, NULL, &e));
	opencl_check_error(clEnqueueReadBuffer(manager->queue, light_buffer,
				CL_TRUE, 0, sizeof(FLOAT3) * scene->cam.w * scene->cam.h, light, 1, &e, NULL));
	//print_light(light, scene->cam.w, scene->cam.h);
	light_to_pixel(light, pixels, scene->cam.w, scene->cam.h);
	free(scene);
	printf("New image rendered.\n");
	return (pixels);
}
