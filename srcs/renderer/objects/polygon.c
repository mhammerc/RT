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
#include "renderer.h"

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
	int		nb_sommet;

	nb_sommet = self->nb_sommet;

	s1 = vec3_sub(*(self->sommet), hit);
	s2 = vec3_sub(self->sommet[nb_sommet - 1], hit);
	if(vec3_dot(normal, vec3_cross(s1, s2)) * self->aire < 0)
		return (0);
	
//	printf("s1 x%f y%f z%f\n", s1.x, s1.y, s1.z);
//	printf("s2 x%f y%f z%f\n", s2.x, s2.y, s2.z);
//	printf("nor x%f y%f z%f\n", normal.x, normal.y, normal.z);
//	printf("aire %d\n\n", aire);
	i = 0;
	while (i < self->nb_sommet - 2)
	{
		s1 = vec3_sub(self->sommet[i], hit);
		s2 = vec3_sub(self->sommet[i + 1], hit);
		if(vec3_dot(normal, vec3_cross(s1, s2)) * self->aire < 0)
			return (0);
		i++;
	}
	return (1);
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

int				polygon_intersect(t_obj *self, t_ray *ray)
{
	t_vec3		x;
	double		a;
	double		b;
	double		d;

	//TODO make dynamical
	self->sommet[0].x = -0.5;
	self->sommet[0].y = 0;
	self->sommet[0].z = 0;
	self->sommet[1].x = 0.1;
	self->sommet[1].y = 0;
	self->sommet[1].z = 0;
	self->sommet[2].x = 0;
	self->sommet[2].y = 10;
	self->sommet[2].z = 0;
	self->dir.x = 0;
	self->dir.y = 0;
	self->dir.z = 1;
	self->nb_sommet = 3;


	if (self->nb_sommet < 3)
		return (0);
	//TODO make function for all case
	t_vec3		s1;
	t_vec3		s2;
	int		nb_sommet;


	nb_sommet = self->nb_sommet;
	s2 = vec3_sub(*(self->sommet), self->sommet[1]);
	s1 = vec3_sub(self->sommet[nb_sommet - 1], self->sommet[1]);
	self->aire = vec3_dot(polygon_normal(self, self->sommet[1]), vec3_cross(s1, s2));
	//
	b = vec3_dot(ray->dir, self->dir);
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(self->pos, ray->pos);
	a = vec3_dot(x, self->dir);
	d = a / b;
	if (d < ray->t && d > 0)
	{
		x = vec3_add(ray->pos, vec3_mult(d, ray->dir));
		if (test_polygon_in(x, polygon_normal(self, x), self))
		{
			ray->t = d;
			if (ray->type == INITIAL_RAY)
				ray->collided = self;
			return (1);
		}
	}
	return (0);
}
