/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:13:40 by racousin          #+#    #+#             */
/*   Updated: 2017/03/15 19:53:11 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in intersecion interval
**
*/

int	inter_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0 || right->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (0);
	}
	return (1);
}
/*
**
**return 1 if 2 intervals are disjoint, 0 else
*/

int	is_disjoint(t_interval *a_i, t_interval *a_j, int i, int j)
{
	return (a_i->max[i].dist < a_j->min[j].dist || a_i->min[i].dist > a_j->max[j].dist);
}
/*
**result in a_i : intersectin between interval *a_i and *a_j
**
*/

void	modify_by_inter(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_i->min[i].dist > a_j->min[j].dist)
	{
		a_i->min[i] = a_j->min[j];
		if (a_i->max[i].dist < a_j->max[j].dist)
			a_i->max[i] = a_j->max[j];
	}
}
/*
**result in interval : intersectin between all interval in right and left
**
*/

void	inter(t_interval *left, t_interval *right, t_interval *interval)
{
	int	l;
	int	r;
	int	i;

	if (!inter_case(left, right, interval))	
		return;
	l = 0;
	i = 0;
	while (l < left->nb_hit)
	{
		interval->min[i] = left->min[l];
		interval->max[i] = left->max[l];
		r = 0;
		while (r < right->nb_hit)
		{
			if (is_disjoint(interval, right, i, r))
				break;
			else
				modify_by_inter(interval, right, i, r);
			r++;
		}
		if (r == right->nb_hit)
			i++;
		l++;
	}
	interval->nb_hit = i;
}

/*
** particulary case solve quickly in substraction interval
**
*/

int	minus_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (0);
	}
	else if (right->nb_hit == 0)
	{
		*interval = *left;
		return (0);
	}
	return (1);
}
/*
**
**test kind intersection : partiel overlap
*/
int	minus_test1(t_interval *a_i, t_interval *a_j, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;
	
	min1 = a_i->min[i].dist;
	max1 = a_i->max[i].dist;
	min2 = a_j->min[j].dist;
	max2 = a_j->max[j].dist;
	if (min1 < min2 && max1 < min2)
		return (0);
	if (min2 < min1 && max2 < min1)
		return (0);
	return (1);
}
/*
**
**test kind intersection : total overlap
*/
int	minus_test0(t_interval *a_i, t_interval *a_j, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;
	
	min1 = a_i->min[i].dist;
	max1 = a_i->max[i].dist;
	min2 = a_j->min[j].dist;
	max2 = a_j->max[j].dist;
	if (min1 > min2 && max1 < max2)
		return (1);
	return (0);
}
/*
**
** modify : creat new segment
*/
void	modify_by_minus2(t_interval *a_i, t_interval *a_j, int i, int *j)
{
	a_i->min[i + 1] = a_j->min[*j];
	a_i->max[i + 1] = a_i->max[i];
	a_i->max[i] = a_i->min[*j];
	(*j)++;
}
void	modify_by_minus3(t_interval *a_i, t_interval *a_j, int i)
{
	a_j->min[a_j->nb_hit] = a_i->min[i];
	a_j->max[a_j->nb_hit] = a_i->max[i];
	(a_j->nb_hit)++;
}

/*
**
**modify : eat a_j in a_i
*/
void	modify_by_minus1(t_interval *a_i, t_interval *a_j, int i, int *j)
{
	if (a_i->min[i].dist < a_j->min[*j].dist)
		a_i->max[i] = a_j->min[*j];
	else
		a_i->min[i] = a_j->max[*j];
	(*j)++;
}

/*
**
**result in interval : left minus right
*/

void	minus(t_interval *left, t_interval *right, t_interval *interval)
{
	int	l;
	int	r;
	int	i;

	if (!(minus_case(left, right, interval)))	
		return;
	l = 0;
	i = 0;
	while (l < left->nb_hit)
	{
			//	printf("what0 l %d\n",l);
		interval->min[i] = left->min[l];
		interval->max[i] = left->max[l];
		r = 0;
		while (r < right->nb_hit)
		{
			//	printf("boucle right\n");
			if (is_disjoint(interval, right, i, r))
			{
			//	printf("disjoint i %d\n", i);
				r++;
			}
			else if (minus_test0(interval, right, i, r))
			{
			//	printf("ecrasement\n");
				break;
			}
			else if (minus_test1(interval, right, i, r))
			{
			//	printf("chevauchement\n");
				modify_by_minus1(interval, right, i, &r);
			}
			else
			{
			//	printf("decoupage\n");
				modify_by_minus2(interval, right, i, &r);
				modify_by_minus3(interval, left, i + 1);
			}
		}
		if  (r == right->nb_hit)
			i++;
		l++;
				//printf("i %d\n", i);
	}
	interval->nb_hit = i;
}

/*
** particulary case solve quickly in union interval
**
*/

int	union_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0 && right->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (1);
	}
	if (left->nb_hit == 0)
	{
		*interval = *right;
		return (1);
	}
	if (right->nb_hit == 0)
	{
		*interval = *left;
		return (1);
	}
	return (0);
}
/*
**
**test overlap //NOTABENE cette fonction nest pas utilise
*/

int	test_union_overlap(t_interval *a, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;
	
	min1 = a->min[i].dist;
	max1 = a->max[i].dist;
	min2 = a->min[j].dist;
	max2 = a->max[j].dist;
	if (min1 < min2 && max1 < min2)
		return (0);
	if (min2 < min1 && max2 < min1)
		return (0);
	return (1);
}

/*
**
**modify : union between a_i and a_j put in a_i
*/
void	modify_by_union(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_j->min[j].dist < a_i->min[i].dist)
		a_i->min[i] = a_j->min[j];
	if (a_j->max[j].dist > a_i->max[i].dist)
		a_i->max[i] = a_j->max[j];
}

/*
**
**result in interval : left union right
*/
void	ft_union(t_interval *left, t_interval *right, t_interval *interval)
{
	int	i;
	int	j;
	int	test[10];

	if (union_case(left, right, interval))
		return;
	i = 0;
	while (i < right->nb_hit)
	{
		left->min[i + left->nb_hit] = right->min[i];
		left->max[i + left->nb_hit] = right->max[i];
		test[i] = 1;
		i++;
	}
	while (i < left->nb_hit + right->nb_hit)
		test[i++] = 1;
	while (i < 10)
		test[i++] = 0;
	i = 0;
	while (i < 9)
	{
		j = i + 1;
		while (j < 10)
		{
			if (test[j])
			{
				if (!is_disjoint(left, left, i, j))
				{
					modify_by_union(left, left, i, j);
					test[j] = 0;
					j = i;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (j < 10)
	{
		if (test[j])
		{
			interval->min[i] = left->min[j];
			interval->max[i] = left->max[j];
			i++;
		}
		j++;
	}
	interval->nb_hit = i;
}

/*
**recursion fonction which run csg tree_obj, and return in intervall, segments cross by ray
**and the ref of the object for each of them
*/

void			test_csg(t_obj *obj, t_ray *ray, t_interval *interval)
{
	t_interval	left;
	t_interval	right;

	if (obj->csg == '0')
		//TODO faire une generique dist_obj(obj, ray) qui remplit interval;
		//pour l'instant uniquement cas sphere :
		{
			obj->intersect(obj, ray, interval);
		}
	else
	{
		test_csg(obj->left, ray, &left);
		test_csg(obj->right, ray, &right);
		if (obj->csg == 'U')
			ft_union(&left, &right, interval);
		else if (obj->csg == 'I')
			inter(&left, &right, interval);
		else if (obj->csg == '-')
			minus(&left, &right, interval);
	}
}

/*
** fill distance minimal positive and ref_obj
** @return 0 if no distance 1 else
** 
*/

int			minimal_positiv(t_interval *interval, t_obj *obj, double *d, t_obj **collided)
{
	int		i;
	int		hit;
	int		location;

	location = LOCATION_NONE;
	if (interval->nb_hit == 0)
		return (LOCATION_NONE);
	i = 0;
	while (i < interval->nb_hit)
	{
		hit = 0;
		if (*d > interval->min[i].dist && interval->min[i].dist > 0)
		{
			*collided = interval->min[i].ref;
			*d = interval->min[i].dist;
			obj->csg_ref = interval->min[i].ref;
			obj->csg_ref->normal_dir = interval->min[i].normal;
			hit = 1;
		}
		if (*d > interval->max[i].dist && interval->max[i].dist > 0)
		{
			*collided = interval->max[i].ref;
			*d = interval->max[i].dist;
			obj->csg_ref = interval->max[i].ref;
			obj->csg_ref->normal_dir = interval->max[i].normal;
			hit = 1;
		}
		if (hit)
		{
			if (0 > interval->min[i].dist && 0 < interval->max[i].dist)
				location = LOCATION_INSIDE;
			else
				location = LOCATION_OUTSIDE;
		}
		i++;
	}
	return (location);
}
/*
** Intersection between ray and csg_obj
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				csg_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	double	d;

	d = BIG_DIST;
	test_csg(self, ray, interval);
	if (interval->nb_hit)
		return (1);
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3			csg_normal(t_obj *self, t_vec3 pos)
{
	t_obj *obj;

	obj = self->csg_ref;
	return(obj->normal(obj, pos));
}
