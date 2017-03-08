/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_disk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:16:37 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 15:28:28 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Intersection between ray and plane
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				disk_intersect(t_obj *self, t_ray *ray)
{
	t_vec3		x;
	t_f			a;
	t_f			b;
	t_f			d;
	t_vec3		pos;

	b = vec3_dot(ray->dir, self->dir);
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(self->pos, ray->pos);
	a = vec3_dot(x, self->dir);
	d = a / b;
	if (d < ray->d && d > 0)
	{
		pos = vec3_add(ray->pos, vec3_mult(d, ray->dir));
		if (vec3_norm(vec3_sub(pos, self->pos)) < self->param)
		{
			ray->d = d;
			if (ray->type == INITIAL_RAY)
				ray->collided = self;
			return (1);
		}
	}
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			disk_normal(t_obj *self, t_vec3 pos)
{
	if (vec3_dot(vec3_sub(pos, self->pos), self->dir) > 0)
		return (self->dir);
	return (vec3_mult(-1, self->dir));
}
