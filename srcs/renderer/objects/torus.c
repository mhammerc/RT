/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 10:32:05 by racousin          #+#    #+#             */
/*   Updated: 2017/03/21 15:09:43 by racousin         ###   ########.fr       */
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

int				torus_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	long double	R = self->radius;
	long double	r = self->length;

	t_vec3	Q = vec3_sub(ray->pos, self->pos);
	long double	u = vec3_dot(self->dir, Q);
	long double	v = vec3_dot(self->dir, ray->dir);

	long double	a = 1. - powl(v, 2.);
	long double	b = 2. * (vec3_dot(Q, ray->dir) - u * v);
	long double	c = vec3_dot(Q, Q) - powl(u, 2.);
	long double	d = vec3_dot(Q, Q) + powl(R, 2.) - powl(r, 2.);

	long double	B = 4. * vec3_dot(Q, ray->dir);
	long double	C = 2. * d + powl(B, 2.) / 4. - 4. * powl(R, 2.) * a;
	long double	D = B * d - 4. * powl(R, 2.) * b;
	long double	E = powl(d, 2.) - 4. * powl(R, 2.) * c + EPS;

	if ((interval->nb_hit = quad4_solve(B,C,D,E, interval)))
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

t_vec3			torus_normal(t_obj *self, t_vec3 pos)
{
	long double		y;
	t_vec3		D;
	t_vec3		X;

	y = vec3_dot(vec3_sub(pos, self->pos), self->dir);
	D = vec3_sub(vec3_sub(pos, self->pos), vec3_mult(y, self->dir));
	X = vec3_mult(self->radius / sqrtl(vec3_dot(D, D)), D);
	if (self->normal_dir == OUTWARDS)
		return (vec3_get_normalized(vec3_sub(pos, vec3_add(self->pos ,X))));
	else
		return (vec3_get_normalized(vec3_sub(vec3_add(self->pos ,X), pos)));
}
