#include <raytracer.h>


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
