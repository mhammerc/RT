/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:13:40 by racousin          #+#    #+#             */
/*   Updated: 2017/03/09 12:48:43 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

struct				s_csg
{
	double	min;
	double	max;
};
typedef				t_csg;

/*
** Intersection between ray and csg_obj
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

//cas none?
void	csg_union(t_csg *left, t_csg *right, t_csg *csg)
{
	if (left->min < right->min)
		csg->min = left->min;
	else
		csg->min = right->min;
	if (left->max > right->max)
		csg->max = left->max;
	else
		csg->max = right->max;
}

void	csg_inter(t_csg *left, t_csg *right, t_csg *csg)
{
	if (left->min < right->min && left->max > right->min)
		csg->min = right->min;
	else if (right->min < left->min && right->max > left->min)
		csg->min = left->min;
//	else
//		return none
	if (left->max > right->max)

		csg->max = right->max;
	else
		csg->max = left->max;
}

void	csg_minus(t_csg *left, t_csg *right, t_csg *csg)
{
	if (left->min < right->min)
		csg->min = left->min;
	else if (left->max < right->max)
		csg->min = left->max;
}

void			csg(t_obj *obj, t_ray *ray, t_csg *csg)
{
	t_csg	left;
	t_csg	right;

	if (obj->csg = '0')
	{
		dist_obj(obj, ray);
		//min
		//max
	}
	else
	{
		//if (obj->left)
			csg(obj->left, ray, &left);
		//if (obj->right)
			csg(obj->right, ray, &right);
		if (obj->csg = 'U')
			csg_union(&left, &right, csg);
		else if (obj->csg = 'I')
		{
		//min
		//max
		}
		else if (obj->csg = '-')
		{
		//min
		//max
		}
	}
}

int				csg_intersect(t_obj *self, t_ray *ray)
{
	if ()
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

t_vec3			csg_normal(t_obj *self, t_vec3 pos)
{
	t_f			m;
	t_vec3		cy_pos;

	m = vec3_dot(self->dir, vec3_sub(pos, self->pos));
	cy_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	return (vec3_get_normalized(vec3_sub(pos, cy_pos)));
}
