/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_disk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:16:37 by vfour             #+#    #+#             */
/*   Updated: 2017/03/22 15:08:07 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <libft.h>
#include <shared.h>
#include <renderer.h>

/*
** Intersection between ray and plane
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				fill_interval_by_disk(t_obj *self, double d,
		t_interval *interval)
{
	interval->nb_hit = 1;
	interval->min[0].dist = d;
	interval->max[0].dist = d;
	interval->min[0].ref = *self;
	interval->max[0].ref = *self;
	return (1);
}

int				disk_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	t_vec3		x;
	double		a;
	double		b;
	double		d;
	t_vec3		pos;

	b = vec3_dot(ray->dir, self->dir);
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(self->pos, ray->pos);
	a = vec3_dot(x, self->dir);
	d = a / b;
	if (d > 0.)
	{
		pos = vec3_add(ray->pos, vec3_mult(d, ray->dir));
		if (vec3_norm(vec3_sub(pos, self->pos)) < self->radius)
			return (fill_interval_by_disk(self, d, interval));
	}
	interval->nb_hit = 0;
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
