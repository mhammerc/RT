/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:19:25 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:19:25 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "renderer.h"

static t_vec3	rand_point(t_vec3 c, double r, unsigned int *seed)
{
	t_vec3	v;
	double	dblr;

	dblr = 2.0 * r;
	v.x = c.x + (double)rand_r(seed) * dblr * INVRANDMAX - r;
	v.y = c.y + (double)rand_r(seed) * dblr * INVRANDMAX - r;
	v.z = c.z + (double)rand_r(seed) * dblr * INVRANDMAX - r;
	return (v);
}

/*
** Generates a random t_vec3 with x, y, and z uniforms
** in the sphere centered in c and of radius r
** @return a random t_vec3
*/

t_vec3			rand_sphere(t_vec3 c, double r, unsigned int *seed)
{
	t_vec3		point;

	point = rand_point(c, r, seed);
	while (vec3_norm(vec3_sub(c, point)) > r)
		point = rand_point(c, r, seed);
	return (point);
}

/*
** Intersects a ray going to one spot with all objects.
** If a transparent object is in the way, accumulates absorbance
** If an opaque object is in the way, black is returned
** @return absorbance of all objects for given ray
*/

t_vec3			absorb_light_ray(t_list *l_obj, t_ray ray)
{
	t_vec3	absorb;

	absorb = (t_vec3){1, 1, 1};
	ray.type = REFLECTION_RAY;
	ray.collided = NULL;
	while (l_obj)
	{
		if (ray_object((t_obj*)l_obj->content, &ray))
		{
			if (ray.collided->transmittance > 0)
				absorb = vec3_mul(absorb, vec3_mult(ray.collided->transmittance,
						get_texture_color(ray)));
			else
			{
				free(ray.collided);
				return ((t_vec3){0, 0, 0});
			}
		}
		l_obj = l_obj->next;
	}
	free(ray.collided);
	return (absorb);
}

/*
** Soft shadows : if a spot is a sphere, averages the absorbances of rays
** aiming at uniformely random points inside the sphere.
** If the spot is punctual, only one ray for absorbance.
** @return absorbance
*/

t_vec3			rt_shadow(t_list *l_obj, t_spot *spot, t_ray ray)
{
	t_vec3	absorb;
	t_vec3	aim;
	int		i;

	absorb = (t_vec3){0, 0, 0};
	i = spot->radius > EPS ? NRAY_SHADOW : 1;
	while (i--)
	{
		aim = rand_sphere(spot->pos, spot->radius, ray.seed);
		ray.dir = vec3_get_normalized(vec3_sub(aim, ray.pos));
		absorb = vec3_add(absorb, absorb_light_ray(l_obj, ray));
	}
	if (spot->radius > EPS)
		return (vec3_mult(1.0 / (double)NRAY_SHADOW, absorb));
	return (absorb);
}
