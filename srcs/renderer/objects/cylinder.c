/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:47:41 by vfour             #+#    #+#             */
/*   Updated: 2017/03/17 10:25:47 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** Intersection between ray and cylinder
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				cylinder_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	double		b;
	double		c;
	t_vec3		vmvva;
	t_vec3		dpmva;

	vmvva = vec3_mult(vec3_dot(ray->dir, self->dir), self->dir);
	vmvva = vec3_sub(ray->dir, vmvva);
	dpmva = vec3_sub(ray->pos, self->pos);
	dpmva = vec3_sub(dpmva, vec3_mult(vec3_dot(dpmva, self->dir), self->dir));
	b = 2 * vec3_dot(vmvva, dpmva);
	c = vec3_dot(dpmva, dpmva) - self->radius;
	if ((interval->nb_hit = quad_solve(vec3_dot(vmvva, vmvva), b, c, interval)))
	{
		interval->min[0].ref = *self;
		interval->max[0].ref = *self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			cylinder_normal(t_obj *self, t_vec3 pos)
{
	double		m;
	t_vec3		cy_pos;

	m = vec3_dot(self->dir, vec3_sub(pos, self->pos));
	cy_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	if (self->normal_dir == INWARDS)
		return (vec3_get_normalized(vec3_sub(cy_pos, pos)));
	else
		return (vec3_get_normalized(vec3_sub(pos, cy_pos)));
}
