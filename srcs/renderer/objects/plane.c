/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:46:56 by vfour             #+#    #+#             */
/*   Updated: 2017/03/15 18:31:57 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "renderer.h"

/*
** Intersection between ray and plane
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				plane_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	t_vec3		x;
	double		a;
	double		b;
	double		d;

	b = vec3_dot(ray->dir, self->dir);
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(self->pos, ray->pos);
	a = vec3_dot(x, self->dir);
	d = a / b;
	interval->nb_hit = 0;
	if (d > 0)
	{
		interval->nb_hit = 1;
		interval->min[0].dist = d;
		interval->max[0].dist = d;
		interval->min[0].ref = self;
		interval->max[0].ref = self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			plane_normal(t_obj *self, t_ray ray)
{
	if (vec3_dot(vec3_sub(ray.pos, self->pos), self->dir) > 0)
		return (self->dir);
	return (vec3_mult(-1, self->dir));
}
