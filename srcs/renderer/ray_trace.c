#include <math.h>
#include "renderer.h"

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/
static int		ray_object(t_obj *obj, t_ray *ray)
{
	t_interval	interval;
	int			location;
	t_obj		*collided;

	location = LOCATION_NONE;
	if (obj->intersect(obj, ray, &interval))
	{
		collided = (t_obj*)malloc(sizeof(t_obj));
		if ((location = minimal_positiv(&interval, obj, &(ray->t), &collided)))
		{
			if (ray->type != OCCLUSION_RAY)
			{
				if (ray->collided)
					free(ray->collided);
				ray->collided = collided;
				ray->location = location;
			}
			else
				free(collided);
		}
		else
			free(collided);
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
	if (collision && ray->type != OCCLUSION_RAY)
	{
		ray->pos = vec3_add(ray->pos, vec3_mult(ray->t - EPS, ray->dir));
		ray->n = ray->collided->normal(ray->collided, ray->pos);
	}
	return (collision);
}

static t_vec3	rt_shadow(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_obj		*obj;
	t_vec3		absorbance;
	double		spot_dist;

	l = sce->obj;
	absorbance = (t_vec3){1, 1, 1};
	spot_dist = ray.t;
	ray.type = REFLECTION_RAY;
	ray.collided = NULL;
	while (l)
	{
		ray.t = spot_dist;
		obj = (t_obj*)l->content;
		if (ray_object(obj, &ray))
		{
			if (ray.collided->transmittance > 0)
			{
				absorbance = vec3_mul(absorbance,
						vec3_mult(ray.collided->transmittance,
							get_texture_color(ray)));
			}
			else
			{
				if (ray.collided)
					free(ray.collided);
				return ((t_vec3){0, 0, 0});
			}
		}
		l = l->next;
	}
	if (ray.collided)
		free(ray.collided);
	return (absorbance);
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
	t_vec3		absorbance;

	obj_cam = vec3_mult(-1, ray.dir);
	light = color_light_mix(get_texture_color(ray),
			sce->ambiant.color,
			sce->ambiant.intensity);
	ray.type = ray.type == REFLECTION_RAY ? REFLECTION_RAY : OCCLUSION_RAY;
	absorbance = (t_vec3){0.0, 0.0, 0.0};
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		absorbance = rt_shadow(sce, ray);
		light = vec3_add(light, color_add_light(ray, spot, obj_cam, absorbance));
		l = l->next;
	}
	return (light);
}


t_vec3			ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;
	t_vec3		refl_light;
	t_ray		new_ray;

	light = (t_vec3){0, 0, 0};
	if (rt_object(sce, &ray))
	{
		ray.dist = ray.dist < 1.0 ? 1.0 : ray.dist + ray.t;
		light = rt_light(sce, ray);
		if (depth < MAX_REC_DEPTH)
		{
			if (ray.collided->reflectance > 0)
			{
				refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
				light = vec3_add(light, color_light_mix(get_texture_color(ray),
							refl_light,
							REFL_ATTENUATION * ray.collided->reflectance / (ray.dist * (1.0 - ray.collided->transmittance))));
			}
			if (ray.collided->transmittance > 0)
			{
				new_ray = refracted_ray(ray);
				if (new_ray.t > 0)
				{
					refl_light = ray_trace(sce, new_ray, depth + 1);
					light = vec3_add(light, color_light_mix(get_texture_color(ray),
								refl_light,
								ray.collided->transmittance));
				}
			}
		}
	}
	if (ray.collided)
		free(ray.collided);
	if (ray.type == REFLECTION_RAY)
		return (vec3_mult(1.0 / ray.dist, light));
	return (light);
}
