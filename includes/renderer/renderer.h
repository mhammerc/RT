#ifndef SCENE_MANAGER_H
# define SCENE_MANAGER_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# elif __linux__
#  include <CL/cl.h>
# endif

# include <libft.h>
# include "shared.h"

# define ALPHA_BITSHIFT 24
# define R_BITSHIFT 0
# define G_BITSHIFT 8
# define B_BITSHIFT 16

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
int						*renderer_compute_image();

void					redraw_scene();

void					opencl_check_error(cl_int error);

/*
** Vectors
*/
FLOAT						vec3_norm(FLOAT3 v);
void						vec3_normalize(FLOAT3 *v);
FLOAT3						vec3_get_normalized(FLOAT3 v);
FLOAT						vec3_norm2(FLOAT3 v);
FLOAT3						vec3_add(FLOAT3 a, FLOAT3 b);
FLOAT3						vec3_cross(FLOAT3 u, FLOAT3 v);
FLOAT						vec3_dot(FLOAT3 a, FLOAT3 b);
FLOAT3						vec3_mult(FLOAT m, FLOAT3 x);
FLOAT3						vec3_sub(FLOAT3 a, FLOAT3 b);

t_cam						camera_set(t_cam cam);

#endif
