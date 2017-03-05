#include <raytracer.h>

int		obj_intersect(__constant t_obj *self, t_ray *ray)
{
	if (self->type == SPHERE)
		return (sphere_intersect(self, ray));
	else
		return (0);
}

float3	obj_normal(__constant t_obj *self, float3 pos)
{
	float3		dummy;

	dummy = (float3)(0, 0, 0);
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	else
		return (dummy);
}

