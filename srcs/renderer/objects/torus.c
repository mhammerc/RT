/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 10:32:05 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 14:36:56 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"
#include <math.h>

/*
** Intersection between ray and torus
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int		torus_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	long double	z[8];
	long double	res[4];
	t_vec3		q;

	q = vec3_sub(ray->pos, self->pos);
	z[2] = vec3_dot(self->dir, q);
	z[3] = vec3_dot(self->dir, ray->dir);
	z[4] = 1. - powl(z[3], 2.);
	z[5] = 2. * (vec3_dot(q, ray->dir) - z[2] * z[3]);
	z[6] = vec3_dot(q, q) - powl(z[2], 2.);
	z[7] = vec3_dot(q, q) + powl(self->radius, 2.) - powl(self->length, 2.);
	res[0] = 4. * vec3_dot(q, ray->dir);
	res[1] = 2. * z[7] + powl(res[0], 2.) / 4. - 4. * powl(self->radius, 2.)
		* z[4];
	res[2] = res[0] * z[7] - 4. * powl(self->radius, 2.) * z[5];
	res[3] = powl(z[7], 2.) - 4. * powl(self->radius, 2.) * z[6] + EPS;
	if ((interval->nb_hit = quad4_solve(res, interval)))
	{
		interval->min[0].ref = *self;
		interval->max[0].ref = *self;
		interval->min[1].ref = *self;
		interval->max[1].ref = *self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3	torus_normal(t_obj *self, t_vec3 pos)
{
	long double	y;
	t_vec3		o;
	t_vec3		x;

	y = vec3_dot(vec3_sub(pos, self->pos), self->dir);
	o = vec3_sub(vec3_sub(pos, self->pos), vec3_mult(y, self->dir));
	x = vec3_mult(self->radius / sqrtl(vec3_dot(o, o)), o);
	if (self->normal_dir == OUTWARDS)
		return (vec3_get_normalized(vec3_sub(pos, vec3_add(self->pos, x))));
	else
		return (vec3_get_normalized(vec3_sub(vec3_add(self->pos, x), pos)));
}
