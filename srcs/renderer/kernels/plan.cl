#include <raytracer.h>
/*
int		    plan_intersect(__constant t_obj *self, t_ray *ray)
{
	float		t;
	float		div;

	div = dot(self->dir, ray->dir);
	if (div)
	{
		t = (dot(self->dir, self->pos) - dot(self->dir, ray->pos)) / div;
		if (t > 0)
		{
			ray->t = t;
			if (ray->type == INITIAL_RAY)
				ray->collided = self->id;
			return (1);
		}
	}
	return (0);
}

float3	    plan_normal(__constant t_obj *self)
{
	return (normalize(self->dir));
}
*/
