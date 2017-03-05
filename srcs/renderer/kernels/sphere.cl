#include <raytracer.h>

int		    sphere_intersect(__constant t_obj *self, t_ray *ray)
{
	float		b;
	float		c;
	float3		ray_sphere;

	ray_sphere = ray->pos - self->pos;
	b = dot(ray_sphere, ray->dir);
	c = dot(ray_sphere, ray_sphere) - self->param;
	if (norm_quad_solve(b, c, &(ray->t)))
	{
		if (ray->type == INITIAL_RAY)
			ray->collided = self->id;
		return (1);
	}
	return (0);
}

float3	    sphere_normal(__constant t_obj *self, float3 pos)
{
	return (normalize(pos - self->pos));
}
