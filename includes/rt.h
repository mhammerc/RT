#ifndef RT_H
# define RT_H

# include <libft.h>

# include "scene_manager.h"
# include "ui.h"
# include "env.h"
# define ALPHA_BITSHIFT 24
# define R_BITSHIFT 0
# define G_BITSHIFT 8
# define B_BITSHIFT 16

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
