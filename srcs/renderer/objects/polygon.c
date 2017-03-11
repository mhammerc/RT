/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:11:10 by racousin          #+#    #+#             */
/*   Updated: 2017/03/09 10:10:40 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Intersection between ray and polygon
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				test_polygon_in(t_vec3 hit, t_vec3 normal, t_obj *self)
{
	int			i;
	t_vec3		s1;
	t_vec3		s2;
	double		aire;

	s1 = vec3_sub(*((self->sommet) + nb_sommet - 1), hit);
	s2 = vec3_sub(*(self->sommet), hit);
	aire = vec3_dot(normal, vec3_cross(s1, s2));
	i = 0;
	while (i < self->nb_sommet - 2)
	{
		s1 = vec3_sub(*((self->sommet) + i), hit);
		s2 = vec3_sub(*((self->sommet) + i + 1), hit);
		if(vec3_dot(normal, vec3_dot(s1, s2)) * aire < 0)
			return (0);
	}
	return (1);
}

int				polygone_intersect(t_obj *self, t_ray *ray)
{
	t_vec3		x;
	t_f			a;
	t_f			b;
	t_f			d;

	if (self->nb_sommet < 3)
		return (0);
	b = vec3_dot(ray->dir, self->dir);
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(self->pos, ray->pos);
	a = vec3_dot(x, self->dir);
	d = a / b;
	if (d < ray->d && d > 0)
	{
		x = vec2_add(ray->pos, vec3_mult(d, ray->dir));
		if (test_polygon_in(x, polygon_norma(self, x), self))
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

t_vec3			polygon_normal(t_obj *self, t_vec3 pos)
{
	if (vec3_dot(vec3_sub(pos, self->pos), self->dir) > 0)
		return (self->dir);
	return (vec3_mult(-1, self->dir));
}
