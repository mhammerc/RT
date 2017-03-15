/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:11:10 by racousin          #+#    #+#             */
/*   Updated: 2017/03/11 18:16:58 by racousin         ###   ########.fr       */
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

int				test_polygon_in(t_vec3 hit, t_vec3 normal, t_obj *self, t_face *face)
{
	int			i;
	t_vec3		s1;
	t_vec3		s2;
	int		nb;

	nb = face->nb;

	s1 = vec3_sub(face->sommets[nb - 1], hit);
	s2 = vec3_sub(face->sommets[0], hit);
	if(vec3_dot(normal, vec3_cross(s1, s2)) * face->aire < 0)
		return (0);
	
//	printf("hit x%f y%f z%f\n", hit.x, hit.y, hit.z);
//	printf("s2 x%f y%f z%f\n", s2.x, s2.y, s2.z);
//	printf("nor x%f y%f z%f\n", normal.x, normal.y, normal.z);
//	printf("aire %d\n\n", aire);
	i = 0;
	while (i < face->nb - 1)
	{
		s1 = vec3_sub(face->sommets[i], hit);
		s2 = vec3_sub(face->sommets[i + 1], hit);
		if(vec3_dot(normal, vec3_cross(s1, s2)) * face->aire < 0)
			return (0);
		i++;
	}
	return (1);
}


/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			face_normal(t_obj *self, t_vec3 pos, t_face *face)
{
//	if (vec3_dot(vec3_sub(pos, face->sommets[1]), *(face->normales)) > 0)
//		return (*(face->normales));
//	return (vec3_mult(-1, *(face->normales)));
	if (vec3_dot(vec3_sub(pos, face->sommets[1]), *(face->normales)) > 0)
		return (*(face->normales));
	return (vec3_mult(-1, *(face->normales)));

}

t_vec3			polygon_normal(t_obj *self, t_ray ray)
{
//	if (vec3_dot(vec3_sub(ray.pos, self->pos), self->face_ref) > 0)
		return ((self->face_ref));
//	return (vec3_mult(-1, self->dir));
}

int				face_intersect(t_obj *self, t_ray *ray, t_face *face)
{
	t_vec3		x;
	double		a;
	double		b;
	double		d;

	if (face->nb < 3)
		return (0);
	//TODO make function for all case
	t_vec3		s1;
	t_vec3		s2;
	t_vec3		normal;
	int			nb;

	nb = face->nb;
	s2 = vec3_sub(face->sommets[0], face->sommets[1]);
	s1 = vec3_sub(face->sommets[nb - 1], face->sommets[1]);
	face->aire = vec3_dot(face_normal(self, face->sommets[1], face), vec3_cross(s1, s2));
	//
	b = vec3_dot(ray->dir, *(face->normales));
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(face->sommets[0], ray->pos);
	a = vec3_dot(x, *(face->normales));
	d = a / b;
	if (d < ray->t && d > 0)
	{
		x = vec3_add(ray->pos, vec3_mult(d, ray->dir));
		if (test_polygon_in(x, face_normal(self, x, face), self, face))
		{
			ray->t = d;
			self->face_ref = face_normal(self, x, face);
			if (ray->type == INITIAL_RAY)
			{
				self->pos = *(face->sommets);
	//TODO problem from here test with or with not printf
	//printf("normal x%f y %f z %f\n", (*(face->normales)).x, (*(face->normales)).y, (*(face->normales)).z);
				self->dir = *(face->normales);
				ray->collided = self;
			}
			return (1);
		}
	}
	return (0);
}

int				polygon_intersect(t_obj *self, t_ray *ray)
{
	if (self->faces)
	{
		int	i;
		int	test;

		i = 0;
		test = 0;
		while (i < self->nb_faces)
		{
			if (test == 0)
				test = face_intersect(self, ray, self->faces + i);
			else
				face_intersect(self, ray, self->faces + i);
			i++;
		}
		return (test);
	}
	return (0);
}
