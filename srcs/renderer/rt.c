/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:04:23 by vfour             #+#    #+#             */
/*   Updated: 2017/03/22 23:41:40 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

int				rt_object(t_scene *sce, t_ray *ray)
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

/*
** Trace a ray from collision point to all light
** If a transparent object is in the way, accumulate absorption
** If an opaque object is in the way, black is returned
** @return absorbance
*/

t_vec3			rt_shadow(t_scene *sce, t_ray ray)
{
	t_list		*l;

	l = sce->obj;
	ray.light = (t_vec3){1, 1, 1};
	ray.dist = ray.t;
	ray.type = REFLECTION_RAY;
	ray.collided = NULL;
	while (l)
	{
		ray.t = ray.dist;
		if (ray_object((t_obj*)l->content, &ray))
		{
			if (ray.collided->transmittance > 0)
				ray.light = vec3_mul(ray.light,
				vec3_mult(ray.collided->transmittance, get_texture_color(ray)));
			else
			{
				free(ray.collided);
				return ((t_vec3){0, 0, 0});
			}
		}
		l = l->next;
	}
	free(ray.collided);
	return (ray.light);
}

/*
** Cast a ray to all lights in scene
** Accumulate light contributions with absorbance
** @return light contributions as a t_vec3
*/

t_vec3			rt_light(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_vec3		obj_cam;
	t_vec3		light;
	t_spot		*spot;
	t_vec3		absorb;

	obj_cam = vec3_mult(-1, ray.dir);
	light = color_light_mix(get_texture_color(ray),
			sce->ambiant.color,
			sce->ambiant.intensity);
	ray.type = ray.type == REFLECTION_RAY ? REFLECTION_RAY : OCCLUSION_RAY;
	absorb = (t_vec3){0.0, 0.0, 0.0};
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		absorb = rt_shadow(sce, ray);
		light = vec3_add(light, color_add_light(ray, spot, obj_cam, absorb));
		l = l->next;
	}
	return (light);
}
