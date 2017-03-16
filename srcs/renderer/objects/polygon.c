/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:11:10 by racousin          #+#    #+#             */
/*   Updated: 2017/03/16 19:45:41 by racousin         ###   ########.fr       */
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

int				test_polygon_in(t_vec3 hit, t_vec3 normal, t_face *face)
{
	unsigned long			i;
	t_vec3		s1;
	t_vec3		s2;
	int		nb;

	nb = face->nb;

	s1 = vec3_sub(face->sommets[nb - 1], hit);
	s2 = vec3_sub(face->sommets[0], hit);
	if(vec3_dot(normal, vec3_cross(s1, s2)) * face->aire < 0.)
		return (0);
	i = 0;
	while (i < face->nb - 1)
	{
		s1 = vec3_sub(face->sommets[i], hit);
		s2 = vec3_sub(face->sommets[i + 1], hit);
		if(vec3_dot(normal, vec3_cross(s1, s2)) * face->aire < 0.)
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
	if (vec3_dot(vec3_sub(pos, self->pos), self->face_ref) > 0.)
		return ((self->face_ref));
	return (vec3_mult(-1, self->dir));
}

double			aire_face_ref(t_face *face)
{
	t_vec3		s1;
	t_vec3		s2;
	int			nb;

	nb = face->nb;
	s2 = vec3_sub(face->sommets[0], face->sommets[1]);
	s1 = vec3_sub(face->sommets[nb - 1], face->sommets[1]);
	return(vec3_dot(*(face->normales), vec3_cross(s1, s2)));
}

int				face_intersect(t_obj *self, t_ray *ray, t_face *face, double *tmp)
{
	t_vec3		x;
	double		a;
	double		b;
	double		d;

	if (face->nb < 3)
		return (0);
	face->aire = aire_face_ref(face);
	b = vec3_dot(ray->dir, *(face->normales));
	if (fabs(b) < EPS)
		return (0);
	x = vec3_sub(face->sommets[0], ray->pos);
	a = vec3_dot(x, *(face->normales));
	d = a / b;
	x = vec3_add(ray->pos, vec3_mult(d, ray->dir));
	if (test_polygon_in(x, *face->normales, face))
	{
		*tmp = d;
		self->face_ref = *(face->normales);
		if (ray->type == INITIAL_RAY)
		{
			self->pos = *(face->sommets);
			self->dir = *(face->normales);
			ray->collided = self;
		}
		return (1);
	}
	return (0);
}

void			sort_interval(t_interval *interval, int	i, int swap, int cmp)
{
	double	tmp;
	int		nb;

	nb = interval->nb_hit;
	while (i < nb)
	{
		tmp = interval->max[i].dist;
		interval->max[i].dist = interval->min[i].dist;
		interval->min[i].dist = swap;
		swap = tmp;
		i++;
	}
	if (cmp % 2)
	{
		interval->max[i].dist = interval->min[i].dist;
		interval->min[i].dist = swap;
	}
	else
	{
		interval->min[i].dist = swap;
		interval->max[i].dist = swap;
	}
}

void			sort_interval_case1(t_interval *interval, int i, double tmp, int cmp)
{
	double	swap;

	swap = interval->max[i].dist;
	interval->max[i].dist = interval->min[i].dist;
	interval->min[i].dist = tmp;
	sort_interval(interval, i + 1, swap, cmp);
}

void			sort_interval_case2(t_interval *interval, int i, double tmp, int cmp)
{
	double	swap;

	swap = interval->max[i].dist;
	interval->max[i].dist = tmp;
	sort_interval(interval, i + 1, swap, cmp);
}

void			adapt_polygon2csg(t_interval *interval, double tmp, int *cmp)
{
	int		i;
	int		nb;

	i = 0;
	nb = interval->nb_hit;
	while (i < nb)
	{
		if (tmp < interval->min[i].dist)
		{
			sort_interval_case1(interval, i, tmp, *cmp);
			break;
		}
		if (tmp < interval->max[i].dist)
		{
			sort_interval_case2(interval, i, tmp, *cmp);
			break;
		}
		i++;
	}
	if (i == nb)
	{
		if (*cmp % 2)
		{
			interval->min[i].dist = tmp;
			interval->max[i].dist = tmp;
		}
		else
		{
			interval->max[i].dist = interval->min[i].dist;
			interval->min[i].dist = tmp;
		}
	}
	(*cmp)++;
	if (*cmp % 2)
		interval->nb_hit++;
}

int				polygon_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	unsigned long	i;
	double			tmp;
	int				cmp;

	interval->nb_hit = 0;
	cmp = 0;
	if (self->faces)
	{
		i = 0;
		while (i < self->nb_faces)
		{
			if (face_intersect(self, ray, self->faces + i, &tmp))
				adapt_polygon2csg(interval, tmp, &cmp);
			i++;
		}
		if (interval->nb_hit != 0)
		{
			interval->min[0].ref = self;
			interval->max[0].ref = self;
		}
	}
	return (interval->nb_hit);
}
