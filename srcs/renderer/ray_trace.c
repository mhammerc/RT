#include "renderer.h"

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/
static int		ray_object(t_obj* obj, t_ray *ray)
{
	t_interval	interval;
	int			location;
	t_obj		*collided;

	collided = NULL;
	location = LOCATION_NONE;
	if (obj->intersect(obj, ray, &interval))
	{
		if ((location = minimal_positiv(&interval, obj, &(ray->t), &collided)))
		{
			if (ray->type == INITIAL_RAY)
			{
				ray->collided = collided;
				ray->location = location;
			}
		}
	}
	return (location == LOCATION_NONE ? 0 : 1);
}

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

static int		rt_object(t_scene *sce, t_ray *ray)
{
	t_list		*l;
	int			collision;
	t_obj		*obj;

	l = sce->obj;
	collision = 0;
	while (l)
	{
		obj = (t_obj*)l->content;
		if (ray_object(obj, ray))
			collision = 1;
		l = l->next;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->pos = vec3_add(ray->pos, vec3_mult(ray->t - EPS, ray->dir));
		ray->n = ray->collided->normal(ray->collided, ray->pos);
	}
	return (collision);
}

/*
** Cast a ray to all lights in scene, accumulate light contributions
** @return light contribution as a t_vec3
*/

static t_vec3	rt_light(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_vec3		obj_cam;
	t_vec3		light;
	t_spot		*spot;

	obj_cam = vec3_mult(-1, ray.dir);
	light = color_light_mix(ray.collided->color,
							sce->ambiant.color,
							sce->ambiant.intensity);
	ray.type = OCCLUSION_RAY;
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		if (!rt_object(sce, &ray))
			light = vec3_add(light, color_add_light(ray, spot, obj_cam));
		l = l->next;
	}
	return (light);
}


t_vec3			ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;
	t_vec3		refl_light;

	light = (t_vec3){0, 0, 0};
	if (depth > MAX_REC_DEPTH)
		return (light);
	if (rt_object(sce, &ray))
	{
		light = rt_light(sce, ray);
		if (ray.collided->kspec > 0)
		{
			refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
			refl_light = vec3_mult(REFL_ATTENUATION, refl_light);
			light = vec3_add(light, color_light_mix(ray.collided->color,
													refl_light,
													ray.collided->kspec));
		}
	}
	return (light);
}
