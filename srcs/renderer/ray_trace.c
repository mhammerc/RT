/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <vfour@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:04:28 by vfour             #+#    #+#             */
/*   Updated: 2017/03/24 14:23:01 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/

int				ray_object(t_obj *obj, t_ray *ray)
{
	t_interval	interval;
	int			location;
	t_obj		*collided;

	interval.nb_hit = 0;
	location = LOCATION_NONE;
	if (obj->intersect(obj, ray, &interval))
	{
		collided = (t_obj*)monloc(sizeof(t_obj));
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

static t_vec3	reflected_light(t_scene *sce,
								t_ray ray,
								int depth)
{
	double		coeff;
	t_vec3		refl_light;

	refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
	coeff = REFL_ATTENUATION * ray.collided->reflectance;
	coeff /= ray.dist * (1.0 - ray.collided->transmittance);
	return (color_light_mix(get_texture_color(ray), refl_light, coeff));
}

static t_vec3	refracted_light(t_scene *sce,
								t_ray ray,
								int depth)
{
	t_vec3		refr_light;
	t_ray		new_ray;

	new_ray = refracted_ray(ray);
	new_ray.type = TRANSMISSION_RAY;
	if (new_ray.t > 0)
	{
		refr_light = ray_trace(sce, new_ray, depth + 1);
		return (color_light_mix(get_texture_color(ray),
				refr_light, ray.collided->transmittance));
	}
	return ((t_vec3){0.0, 0.0, 0.0});
}

t_vec3			ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;

	light = (t_vec3){0.0, 0.0, 0.0};
	if (rt_object(sce, &ray))
	{
		ray.dist = ray.dist < 1.0 ? 1.0 : ray.dist + ray.t;
		ray.seed = &sce->seed;
		light = rt_light(sce, ray);
		if (depth < MAX_REC_DEPTH)
		{
			if (ray.collided->reflectance > 0)
				light = vec3_add(light, reflected_light(sce, ray, depth));
			if (ray.collided->transmittance > 0)
				light = vec3_add(light, refracted_light(sce, ray, depth));
			if (sce->filter == GLOBAL_ILLUM)
				light = vec3_add(light, global_illum(sce, ray, depth));
		}
	}
	if (ray.collided)
		free(ray.collided);
	if (ray.type != TRANSMISSION_RAY)
		return (vec3_mult(1.0 / (ray.dist * ray.dist), light));
	else
		return (light);
}
