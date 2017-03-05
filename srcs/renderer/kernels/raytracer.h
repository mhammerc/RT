#ifndef RAYTRACER_H
# define RAYTRACER_H

# include <shared.h>

int			sphere_intersect(__constant t_obj *self, t_ray *ray);
float3		sphere_normal(__constant t_obj *self, float3 pos);

float3		obj_normal(__constant t_obj *self, float3 pos);
int			obj_intersect(__constant t_obj *self, t_ray *ray);

int			norm_quad_solve(float b, float c, float *t);

#endif
