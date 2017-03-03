#include <env.h>

static int		norm_quad_solve(float b, float c, float *t)
{
	float		d;
	float		x1;
	float		x2;
	int			res;

	d = b * b - c;
	if (d < 0.)
		return (0);
	res = 0;
	d = sqrt(d);
	x1 = -b - d;
	x2 = -b + d;
	if (x1 > 0. && x1 < *t)
	{
		res = 1;
		*t = x1;
	}
	if (x2 > 0. && x2 < *t)
	{
		res = 1;
		*t = x2;
	}
	return (res);
}

static int		sphere_intersect(__constant t_obj *self, t_ray *ray)
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

static float3	sphere_normal(__constant t_obj *self, float3 pos)
{
	return (normalize(pos - self->pos));
}

static int		obj_intersect(__constant t_obj *self, t_ray *ray)
{
	if (self->type == SPHERE)
		return (sphere_intersect(self, ray));
	//calls for intersection of other types of object go here
	else
		return (0);
}

static float3	obj_normal(__constant t_obj *self, float3 pos)
{
	float3		dummy;

	dummy = (float3)(0, 0, 0);
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	//calls for normal of other types of object go here
	else
		return (dummy);
}

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

static int		rt_object(__constant t_obj *obj, int nb_obj, t_ray *ray)
{
	int			collision;

	collision = 0;
	for (int i = 0; i < nb_obj; ++i)
	{
		if (obj_intersect((obj + i), ray))
			collision = 1;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->hit = ray->pos + (ray->t - (float)EPS) * ray->dir;
		ray->n = obj_normal(obj + ray->collided, ray->hit);
	}
	return (collision);
}

__kernel void	compute_color(__global float3* light,
								__constant t_cl_scene *sce,
								__constant t_obj *obj,
								__constant t_spot *spot)
{
	int			pos;
	t_ray		ray;
	int			i;
	int			j;

	pos = get_global_id(0);
	j = pos % sce->cam.w;
	i = pos / sce->cam.w;
	ray.pos = sce->cam.pos;
	ray.dir = normalize(sce->cam.top_left - (float)i * sce->cam.vy + (float)j * sce->cam.vx - ray.pos);
	ray.n = 0.0;
	ray.t = BIG_DIST + 1;
	//ray.type = INITIAL_RAY;
	ray.type = OCCLUSION_RAY;
	ray.collided = 0;
	ray.hit = 0.0;
	ray.color = 0.0;

	/*
	light[pos].x = ray.dir.x;
	light[pos].y = ray.dir.y;
	light[pos].z = ray.dir.z;
	*/
	if (rt_object(obj, sce->nb_obj, &ray))
	{
		//light[pos] = rt_light(obj, sce->nb_obj, spot, sce->nb_spot, sce->ambiant, ray);
		light[pos].x = 1.0 / ray.t;
		light[pos].y = 1.0 / ray.t;
		light[pos].z = 1.0 / ray.t;
	}
}

