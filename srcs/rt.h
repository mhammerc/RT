#ifndef RT_H
# define RT_H

# include <libft.h>

# include "scene_manager.h"
# include "interface.h"
# include "env.h"
# define R_BITSHIFT 16
# define G_BITSHIFT 8
# define B_BITSHIFT 0

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
