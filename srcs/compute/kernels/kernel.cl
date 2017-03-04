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
	else
		return (0);
}

static float3	obj_normal(__constant t_obj *self, float3 pos)
{
	float3		dummy;

	dummy = (float3)(0, 0, 0);
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	else
		return (dummy);
}

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

static float3	rt_light(__constant t_obj *obj,
						__constant t_spot *spot,
						__constant t_cl_scene *sce,
						t_ray ray)
{
	float3		light;
	float		diff;
	float3		h;
	float3		obj_cam;

	light.x = sce->ambiant.color.x * obj[ray.collided].color.x * sce->ambiant.intensity;
	light.y = sce->ambiant.color.y * obj[ray.collided].color.y * sce->ambiant.intensity;
	light.z = sce->ambiant.color.z * obj[ray.collided].color.z * sce->ambiant.intensity;
	obj_cam = -ray.dir;
	ray.type = OCCLUSION_RAY;
	for(int i = 0; i < sce->nb_spot; ++i)
	{
		ray.dir = normalize(spot[i].pos - ray.pos);
		if (!rt_object(obj, sce->nb_obj, &ray))
		{
			diff = dot(ray.dir, ray.n);
			diff = diff > 0.0 ? diff : 0.0;
			if (diff > 0.0)
			{
				diff *= obj[ray.collided].kdiff * spot[i].intensity;
				light.x += spot[i].color.x * obj[ray.collided].color.x * diff;
				light.y += spot[i].color.y * obj[ray.collided].color.y * diff;
				light.z += spot[i].color.z * obj[ray.collided].color.z * diff;
			}
			h = normalize(obj_cam + ray.dir);
			diff = pow(dot(ray.n, h), obj[ray.collided].kp);
			diff = diff > 0.0 ? diff : 0.0;
			if (diff > 0.0)
			{
				diff *= obj[ray.collided].kspec * spot[i].intensity;
				light.x += spot[i].color.x * obj[ray.collided].color.x * diff;
				light.y += spot[i].color.y * obj[ray.collided].color.y * diff;
				light.z += spot[i].color.z * obj[ray.collided].color.z * diff;
			}
		}
	}
	return (light);
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
	ray.type = INITIAL_RAY;
	ray.collided = 0;
	ray.hit = 0.0;
	ray.color = 0.0;

	if (rt_object(obj, sce->nb_obj, &ray))
		light[pos] = rt_light(obj, spot, sce, ray);
}

