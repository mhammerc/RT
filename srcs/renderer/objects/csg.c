/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:13:40 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 20:46:09 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
**return 1 if 2 intervals are disjoint, 0 else
*/

int			is_disjoint(t_interval *a_i, t_interval *a_j, int i, int j)
{
	return (a_i->max[i].dist < a_j->min[j].dist ||
			a_i->min[i].dist > a_j->max[j].dist);
}

/*
**recursion fonction which run csg tree_obj,
**and return in intervall, segments cross by ray
**and the ref of the object for each of them
*/

void		test_csg(t_obj *obj, t_ray *ray, t_interval *interval)
{
	t_interval	left;
	t_interval	right;

	if (obj->csg == '0')
		obj->intersect(obj, ray, interval);
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
** Intersection between ray and csg_obj
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int			csg_intersect(t_obj *self, t_ray *ray, t_interval *interval)
{
	test_csg(self, ray, interval);
	if (interval->nb_hit)
		return (1);
	return (0);
}

/*
** Normal vector at given point
** @return normal direction
*/

t_vec3		csg_normal(t_obj *self, t_vec3 pos)
{
	t_obj *obj;

	obj = self->csg_ref;
	return (obj->normal(obj, pos));
}
