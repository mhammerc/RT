/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 10:32:05 by racousin          #+#    #+#             */
/*   Updated: 2017/03/16 18:13:56 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "renderer.h"

/*
** Intersection between ray and torus
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int			quad4_solve(double a, double b, double c, double d, double e, double *root);
int				torus_intersect(t_obj *self, t_ray *ray)
{

	self->radius = 1;
	self->length = 0.2;
	self->dir.x = 0;
	self->dir.y = 0;
	self->dir.z = 1;
	self->kdiff = 1;
	self->kspec = 1;
	ray->dir = vec3_get_normalized(ray->dir);

	double	R = self->radius;
	double	r = self->length;

	t_vec3	Q = vec3_sub(ray->pos, self->pos);
	double	u = vec3_dot(self->dir, Q);
	double	v = vec3_dot(self->dir, ray->dir);

	double	a = 1 - pow(v, 2);
	double	b = 2 * (vec3_dot(Q, ray->dir) - u * v);
	double	c = vec3_dot(Q, Q) - pow(u, 2);
	double	d = vec3_dot(Q, Q) + pow(R, 2) - pow(r, 2);

	double	A = 1;
	double	B = 4 * vec3_dot(Q, ray->dir);
	double	C = 2 * d + pow(B, 2) / 4. - 4 * pow(R, 2) * a;
	double	D = B * d - 4 * pow(R, 2) * b;
	double	E = pow(d, 2) - 4 * pow(R, 2) * c;

	if (quad4_solve(A,B,C,D,E, &(ray->t)))
	{
		if (ray->type == INITIAL_RAY)
			ray->collided = self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			torus_normal(t_obj *self, t_ray ray)
{
	double		y;
	t_vec3		D;
	t_vec3		X;

	y = vec3_dot(vec3_sub(ray.pos, self->pos), self->dir);
	D = vec3_sub(vec3_sub(ray.pos, self->pos), vec3_mult(y, self->dir));
	X = vec3_mult(self->radius / sqrt(vec3_dot(D, D)), D);
	return (vec3_get_normalized(vec3_sub(ray.pos, vec3_add(self->pos ,X))));
}

/*
** intersect intervall between ray and cylindre, interval->hit is 0 if no intersection 1 else
** @return 1
**
*/
/*
int				cylinder_intersect_csg(t_obj *obj, t_ray *ray, t_interval *interval)
{
	double		b;
	double		c;
	t_vec3		vmvva;
	t_vec3		dpmva;

	vmvva = vec3_mult(vec3_dot(ray->dir, obj->dir), obj->dir);
	vmvva = vec3_sub(ray->dir, vmvva);
	dpmva = vec3_sub(ray->pos, obj->pos);
	dpmva = vec3_sub(dpmva, vec3_mult(vec3_dot(dpmva, obj->dir), obj->dir));
	b = 2 * vec3_dot(vmvva, dpmva);
	c = vec3_dot(dpmva, dpmva) - obj->param;
	if ((interval->nb_hit = quad_solve2(vec3_dot(vmvva, vmvva), b, c, interval)))
	{
		interval->min[0].ref = obj;
		interval->max[0].ref = obj;
	}
	return (1);
}
*/
/*
** Normal vector at given point
*/
/*
t_vec3			cylinder_normal_csg(t_obj *obj, t_vec3 pos)
{
	double		m;
	t_vec3		cy_pos;

	//TODO if(!obj->csg_normal)
	m = vec3_dot(obj->dir, vec3_sub(pos, obj->pos));
	cy_pos = vec3_add(obj->pos, vec3_mult(m, obj->dir));
	return (vec3_get_normalized(vec3_sub(pos, cy_pos)));
}
*/
