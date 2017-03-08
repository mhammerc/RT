#ifndef SCENE_MANAGER_H
# define SCENE_MANAGER_H

# include <libft.h>
# include "shared.h"

# define ALPHA_BITSHIFT 24
# define R_BITSHIFT 0
# define G_BITSHIFT 8
# define B_BITSHIFT 16

int			*renderer_compute_image();

void		redraw_scene();

/*
** Vectors
*/
double		vec3_norm(t_vec3 v);
void		vec3_normalize(t_vec3 *v);
t_vec3		vec3_get_normalized(t_vec3 v);
double		vec3_norm2(t_vec3 v);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 u, t_vec3 v);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult(double m, t_vec3 x);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);

t_cam		camera_set(t_cam cam);

int			sphere_intersect(t_obj *self, t_ray *ray)
t_vec3		sphere_normal(t_obj *self, t_vec3 pos)

int(*) (struct obj*, t_ray*)	get_obj_intersection(enum e_object_type);
t_vec3(*) (struct obj*, t_vec3)	get_obj_normal(enum e_object_type);

#endif
