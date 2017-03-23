/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:04:23 by vfour             #+#    #+#             */
/*   Updated: 2017/03/23 12:36:01 by vfour            ###   ########.fr       */
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
	ray.seed = &sce->seed;
	absorb = (t_vec3){0.0, 0.0, 0.0};
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		absorb = rt_shadow(sce->obj, spot, ray);
		light = vec3_add(light, color_add_light(ray, spot, obj_cam, absorb));
		l = l->next;
	}
	return (light);
}
