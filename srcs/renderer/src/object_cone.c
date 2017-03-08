/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:48:05 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:54:31 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Intersection between ray and cone
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

static int		cone_intersect(t_obj *self, t_ray *ray)
{
	t_f			a[6];
	t_vec3		vmvva;
	t_vec3		dpmva;
	t_vec3		dp;

	dp = vec3_sub(ray->pos, self->pos);
	a[4] = vec3_dot(ray->dir, self->dir);
	vmvva = vec3_sub(ray->dir, vec3_mult(a[4], self->dir));
	a[5] = vec3_dot(dp, self->dir);
	dpmva = vec3_sub(dp, vec3_mult(a[5], self->dir));
	a[0] = self->param * self->param;
	a[3] = 1.0 - a[0];
	a[2] = a[0] * vec3_norm2(dpmva) - a[3] * a[5] * a[5];
	a[1] = 2 * (a[0] * vec3_dot(vmvva, dpmva) - a[3] * a[4] * a[5]);
	a[0] = a[0] * vec3_norm2(vmvva) - a[3] * a[4] * a[4];
	if (quad_solve(a[0], a[1], a[2], &(ray->d)))
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

static t_vec3	cone_normal(t_obj *self, t_vec3 pos)
{
	t_f			m;
	t_vec3		c_pos;
	t_vec3		apex_to_pos;

	apex_to_pos = vec3_sub(pos, self->pos);
	m = vec3_norm(apex_to_pos) / sqrt(self->param);
	if (vec3_dot(self->dir, apex_to_pos) < 0)
		m = -m;
	c_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	return (vec3_get_normalized(vec3_sub(pos, c_pos)));
}

static t_obj	*check_cone(t_obj *o)
{
	if (!float_checkbounds(o->color.r, 0, 1)
		|| !float_checkbounds(o->color.g, 0, 1)
		|| !float_checkbounds(o->color.b, 0, 1)
		|| !float_checkbounds(RAD_TO_DEG * o->param, EPS, MAX_CONE_ANGLE)
		|| !float_checkbounds(o->kp, 0, MAX_KP)
		|| !float_checkbounds(o->kspec, 0, MAX_KSPEC)
		|| !float_checkbounds(o->kdiff, 0, MAX_KDIFF))
	{
		ft_putendl("Cone : out of bound value");
		free(o);
		return (NULL);
	}
	return (o);
}

/*
** cone constructor
** Beware : cosine of cone angle is stored
** @return a pointer to a new struct cone, or null
*/

t_obj			*cone_new(char **t)
{
	t_obj		*o;
	t_f			color_normalize;

	if (NULL == (o = (t_obj*)ft_memalloc(sizeof(t_obj))))
		ft_exit("Malloc error in Sphere constructor", EXIT_FAILURE);
	color_normalize = 1. / 255.;
	o->pos = (t_vec3){ft_atof(*t), ft_atof(*(t + 1)), ft_atof(*(t + 2))};
	o->dir = (t_vec3){ft_atof(*(t + 3)), ft_atof(*(t + 4)), ft_atof(*(t + 5))};
	vec3_normalize(&(o->dir));
	o->param = ft_atof(*(t + 6));
	o->param = cos(o->param * DEG_TO_RAD);
	o->color.r = (t_f)ft_atoi(*(t + 7)) * color_normalize;
	o->color.g = (t_f)ft_atoi(*(t + 8)) * color_normalize;
	o->color.b = (t_f)ft_atoi(*(t + 9)) * color_normalize;
	o->kspec = ft_atof(*(t + 10));
	o->kdiff = ft_atof(*(t + 11));
	o->kp = ft_atof(*(t + 12));
	o->intersect = &cone_intersect;
	o->normal = &cone_normal;
	return (check_cone(o));
}
