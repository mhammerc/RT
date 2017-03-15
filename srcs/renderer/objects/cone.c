/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:48:05 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 15:27:53 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"
#include "math.h"

/*
** Intersection between ray and cone
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				cone_intersect(t_obj *self, t_ray *ray)
{
	double		a[6];
	t_vec3		vmvva;
	t_vec3		dpmva;
	t_vec3		dp;

	dp = vec3_sub(ray->pos, self->pos);
	a[4] = vec3_dot(ray->dir, self->dir);
	vmvva = vec3_sub(ray->dir, vec3_mult(a[4], self->dir));
	a[5] = vec3_dot(dp, self->dir);
	dpmva = vec3_sub(dp, vec3_mult(a[5], self->dir));
	a[0] = self->radius * self->radius;
	a[3] = 1.0 - a[0];
	a[2] = a[0] * vec3_norm2(dpmva) - a[3] * a[5] * a[5];
	a[1] = 2 * (a[0] * vec3_dot(vmvva, dpmva) - a[3] * a[4] * a[5]);
	a[0] = a[0] * vec3_norm2(vmvva) - a[3] * a[4] * a[4];
	if (quad_solve(a[0], a[1], a[2], &(ray->t)))
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

t_vec3			cone_normal(t_obj *self, t_vec3 pos)
{
	double		m;
	t_vec3		c_pos;
	t_vec3		apex_to_pos;

	apex_to_pos = vec3_sub(pos, self->pos);
	m = vec3_norm(apex_to_pos) / sqrt(self->radius);
	if (vec3_dot(self->dir, apex_to_pos) < 0)
		m = -m;
	c_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	return (vec3_get_normalized(vec3_sub(pos, c_pos)));
}

/*
** intersect intervall between ray and cylindre, interval->hit is 0 if no intersection 1 else
** @return 1
**
*/

int			cone_intersect_csg(t_obj *self, t_ray *ray, t_interval *interval)
{
	double		a[6];
	t_vec3		vmvva;
	t_vec3		dpmva;
	t_vec3		dp;

	dp = vec3_sub(ray->pos, self->pos);
	a[4] = vec3_dot(ray->dir, self->dir);
	vmvva = vec3_sub(ray->dir, vec3_mult(a[4], self->dir));
	a[5] = vec3_dot(dp, self->dir);
	dpmva = vec3_sub(dp, vec3_mult(a[5], self->dir));
	a[0] = self->radius * self->radius;
	a[3] = 1.0 - a[0];
	a[2] = a[0] * vec3_norm2(dpmva) - a[3] * a[5] * a[5];
	a[1] = 2 * (a[0] * vec3_dot(vmvva, dpmva) - a[3] * a[4] * a[5]);
	a[0] = a[0] * vec3_norm2(vmvva) - a[3] * a[4] * a[4];
	if ((interval->nb_hit = quad_solve2(a[0], a[1], a[2], interval)))
	{
		interval->min[0].ref = self;
		interval->max[0].ref = self;
	}
	return (1);
}

/*
** Normal vector at given point
*/

t_vec3			cone_normal_csg(t_obj *self, t_vec3 pos)
{
	double		m;
	t_vec3		c_pos;
	t_vec3		apex_to_pos;

	//TODO if(!obj->csg_normal)
	apex_to_pos = vec3_sub(pos, self->pos);
	m = vec3_norm(apex_to_pos) / sqrt(self->radius);
	if (vec3_dot(self->dir, apex_to_pos) < 0)
		m = -m;
	c_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	return (vec3_get_normalized(vec3_sub(pos, c_pos)));
}
