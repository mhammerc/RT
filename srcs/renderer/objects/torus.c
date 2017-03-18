/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 10:32:05 by racousin          #+#    #+#             */
/*   Updated: 2017/03/18 19:49:17 by racousin         ###   ########.fr       */
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

	//self->radius = 1;
	self->length = 0.2;
	//self->dir.x = EPS;
	//self->dir.y = EPS;
	//self->dir.z = EPS;
	//self->kdiff = 1;
	//self->kspec = 1;
	ray->dir = vec3_get_normalized(ray->dir);

	if (!(cylinder_intersect(self,ray, interval)))
		return (0);
	double	R = self->radius;
	double	r = self->length;

	t_vec3	Q = vec3_sub(ray->pos, self->pos);
	double	u = vec3_dot(self->dir, Q);
	double	v = vec3_dot(self->dir, ray->dir);

	double	a = 1. - pow(v, 2.);
	double	b = 2. * (vec3_dot(Q, ray->dir) - u * v);
	double	c = vec3_dot(Q, Q) - pow(u, 2.);
	double	d = vec3_dot(Q, Q) + pow(R, 2.) - pow(r, 2.);

	double	A = 1.;
	double	B = 4. * vec3_dot(Q, ray->dir);
	double	C = 2. * d + pow(B, 2.) / 4. - 4. * pow(R, 2.) * a;
	double	D = B * d - 4. * pow(R, 2.) * b;
	double	E = pow(d, 2.) - 4. * pow(R, 2.) * c + EPS;

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
	double		y;
	t_vec3		D;
	t_vec3		X;

	y = vec3_dot(vec3_sub(pos, self->pos), self->dir);
	D = vec3_sub(vec3_sub(pos, self->pos), vec3_mult(y, self->dir));
	X = vec3_mult(self->radius / sqrt(vec3_dot(D, D)), D);
	if (self->normal_dir == OUTWARDS)
		return (vec3_get_normalized(vec3_sub(pos, vec3_add(self->pos ,X))));
	else
		return (vec3_get_normalized(vec3_sub(vec3_add(self->pos ,X), pos)));
}
