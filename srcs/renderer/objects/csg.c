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
#include "renderer.h"

/*
** Intersection between ray and csg_obj
** @return the distance between camera and object if there is collision
** or a negative value otherwise
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

int	is_disjoint(t_interval *a_i, t_interval *a_j, int i, int j)
{
	return (a_i->max[i].dist < a_j->min[j].dist || a_i->min[i].dist > a_j->max[j].dist);
}

void	modify_by_inter(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_i->min[i].dist > a_j->min[j].dist)
	{
		a_i->min[i] = a_j->min[j];
		if (a_i->max[i].dist < a_j->max[j].dist)
			a_i->max[i] = a_j->max[j];
	}
}

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
		interval->min[i] = left->min[i];
		interval->max[i] = left->max[i];
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

void			test_csg(t_obj *obj, t_ray *ray, t_interval *interval)
{
	t_interval	left;
	t_interval	right;

	if (obj->csg == '0')
		//TODO faire une generique dist_obj(obj, ray) qui remplit interval;
		//pour l'instant uniquement cas sphere :
		{
			double		b;
			double		c;
			t_vec3		ray_sphere;

			ray_sphere = vec3_sub(ray->pos, obj->pos);
			b = vec3_dot(ray_sphere, ray->dir);
			c = vec3_norm2(ray_sphere) - obj->param;
			if((interval->nb_hit = norm_quad_solve2(b, c, interval)))
			{
				interval->min[0].ref_normal = obj;
				interval->max[0].ref_normal = obj;
			}
			
		}
	else
	{
		test_csg(obj->left, ray, &left);
		test_csg(obj->right, ray, &right);
		if (obj->csg == 'U')
			inter(&left, &right, interval);
		else if (obj->csg == 'I')
			inter(&left, &right, interval);
		else if (obj->csg == '-')
			inter(&left, &right, interval);
	}
}

int				csg_intersect(t_obj *self, t_ray *ray)
{
	t_interval	interval;
	double	d;
	//TODO A REMPLIR DYNAMIQUEMENT
	t_obj	left;
	t_obj	left_left;
	t_obj	left_right;
	t_obj	right;
	left = *self;
	right = *self;
	left.pos.x=-1;
	right.pos.x=0;
	self->csg = 'I';
	self->left = &left;
	self->right = &right;
	self->left->csg = 'I';
	left_right = left;
	left_left = left;
	self->left->left = &left_left;
	self->left->right = &left_right;
	self->left->left->param = 1;
	self->left->right->param = 1;
	self->left->left->csg = '0';
	self->left->right->csg = '0';
	self->right->csg = '0';
	self->right->param = 1;
	//
	test_csg(self, ray, &interval);
	if (interval.nb_hit)
	{
		d = interval.min[0].dist;//TODO CALCULER LE MIN POSITIF
		self->csg_normal_ref = interval.min[0].ref_normal;
		if (d > 0)
		{
			ray->t = d;
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

t_vec3			csg_normal(t_obj *self, t_vec3 pos)
{
	t_obj *obj;

	obj = self->csg_normal_ref;
	if(!self->csg_normal)
	{
	return (vec3_get_normalized(vec3_sub(pos, obj->pos)));
	}
	else
	{
		printf("test2");
	return (vec3_get_normalized(vec3_sub(obj->pos, pos)));
	}
}
