/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:55:18 by vfour             #+#    #+#             */
/*   Updated: 2017/03/22 22:55:54 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

/*
** Ray constructor
** @return a new ray
*/

t_ray		ray_new(t_vec3 pos, t_vec3 aim)
{
	t_vec3	n;
	t_vec3	dir;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, BIG_DIST + 1,
			INITIAL_RAY, NULL, n, stack_new(), LOCATION_NONE, 0.0});
}

/*
** From a previous ray, creates a new ray ready for tracing with new direction
*/

t_ray		ray_new_dir(t_ray ray, t_vec3 dir)
{
	t_vec3	n;

	n = (t_vec3){0, 0, 0};
	ray.dir = dir;
	ray.t = BIG_DIST + 1;
	ray.n = n;
	ray.type = INITIAL_RAY;
	ray.collided = NULL;
	ray.location = LOCATION_NONE;
	return (ray);
}

t_ray		reflected_ray(t_ray ray)
{
	t_vec3	refl;

	refl = vec3_mult(-1, ray.dir);
	refl = vec3_add(ray.pos, vec3_mult(2 * vec3_dot(ray.n, refl), ray.n));
	refl = vec3_add(refl, ray.dir);
	refl = vec3_sub(refl, ray.pos);
	ray = ray_new_dir(ray, vec3_get_normalized(refl));
	ray.type = REFLECTION_RAY;
	return (ray);
}

static void	get_refraction_index(t_ray ray, double *ki, double *kr)
{
	t_obj	*prev_obj;

	if (ray.location == LOCATION_OUTSIDE)
	{
		prev_obj = stack_peak(&(ray.rstack));
		*ki = (NULL == prev_obj) ? R_DEFAULT : prev_obj->rindex;
		*kr = ray.collided->rindex;
		stack_push(&(ray.rstack), ray.collided);
	}
	else
	{
		stack_pop(&(ray.rstack));
		prev_obj = stack_peak(&(ray.rstack));
		*kr = (NULL == prev_obj) ? R_DEFAULT : prev_obj->rindex;
		*ki = ray.collided->rindex;
	}
}

t_ray		refracted_ray(t_ray ray)
{
	double	ki;
	double	kr;
	double	c1;
	double	cs2;
	t_vec3	new_dir;

	get_refraction_index(ray, &ki, &kr);
	ki = ki / kr;
	c1 = vec3_dot(ray.dir, ray.n);
	kr = (0.0 < c1) ? -1.0 : 1.0;
	c1 = c1 > 0 ? c1 : -c1;
	cs2 = 1.0 - ki * ki * (1.0 - c1 * c1);
	if (cs2 < 0.0)
	{
		ray.t = -1.0;
		return (ray);
	}
	new_dir = vec3_mult(ki, ray.dir);
	new_dir = vec3_add(T, vec3_mult(kr * (ki * c1 - sqrt(cs2)), ray.n));
	ray.pos = vec3_add(ray.pos, vec3_mult(2. * EPS, ray.dir));
	return (ray_new_dir(ray, vec3_get_normalized(T)));
}
