/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:35:22 by vfour             #+#    #+#             */
/*   Updated: 2017/03/15 19:23:33 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** Intersection between ray and sphere
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				sphere_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	double		b;
	double		c;
	t_vec3		ray_sphere;

	ray_sphere = vec3_sub(ray->pos, self->pos);
	b = vec3_dot(ray_sphere, ray->dir);
	c = vec3_norm2(ray_sphere) - self->radius;
	if((interval->nb_hit = norm_quad_solve(b, c, interval)))
	{
		interval->min[0].ref = self;
		interval->max[0].ref = self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
*/

t_vec3			sphere_normal(t_obj *self, t_ray ray)
{
	if (self->normal_dir == OUTWARDS)
		return (vec3_get_normalized(vec3_sub(pos, self->pos)));
	else
		return (vec3_get_normalized(vec3_sub(self->pos, pos)));
}
