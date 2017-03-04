#ifndef SCENE_MANAGER_H
# define SCENE_MANAGER_H

# include <OpenCL/opencl.h>

typedef struct			s_scene_manager
{
	cl_uint					platforms_count;
	cl_platform_id			platform_id;

	cl_uint					devices_count;
	cl_device_id			device_id;
	cl_device_id			*device_ids;

	cl_context_properties	context_properties[4];
	cl_context				context;

	cl_command_queue		queue;

	cl_program				program;
}						t_scene_manager;

t_scene_manager			*opencl_get();
void					opencl_init();
void					opencl_create_program(t_scene_manager *manager,
		const char **sources, size_t sources_count);
int						*opencl_compute_image();

void					redraw_scene();

#endif
