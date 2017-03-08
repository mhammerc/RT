/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:47:41 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:47:36 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Intersection between ray and cylinder
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

static int		cylinder_intersect(t_obj *self, t_ray *ray)
{
	t_f			b;
	t_f			c;
	t_vec3		vmvva;
	t_vec3		dpmva;

	vmvva = vec3_mult(vec3_dot(ray->dir, self->dir), self->dir);
	vmvva = vec3_sub(ray->dir, vmvva);
	dpmva = vec3_sub(ray->pos, self->pos);
	dpmva = vec3_sub(dpmva, vec3_mult(vec3_dot(dpmva, self->dir), self->dir));
	b = 2 * vec3_dot(vmvva, dpmva);
	c = vec3_dot(dpmva, dpmva) - self->param;
	if (quad_solve(vec3_dot(vmvva, vmvva), b, c, &(ray->d)))
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

static t_vec3	cylinder_normal(t_obj *self, t_vec3 pos)
{
	t_f			m;
	t_vec3		cy_pos;

	m = vec3_dot(self->dir, vec3_sub(pos, self->pos));
	cy_pos = vec3_add(self->pos, vec3_mult(m, self->dir));
	return (vec3_get_normalized(vec3_sub(pos, cy_pos)));
}

static t_obj	*check_cylinder(t_obj *o)
{
	if (!float_checkbounds(o->color.r, 0, 1)
		|| !float_checkbounds(o->color.g, 0, 1)
		|| !float_checkbounds(o->color.b, 0, 1)
		|| !float_checkbounds(o->param, EPS, MAX_RADIUS)
		|| !float_checkbounds(o->kp, 0, MAX_KP)
		|| !float_checkbounds(o->kspec, 0, MAX_KSPEC)
		|| !float_checkbounds(o->kdiff, 0, MAX_KDIFF))
	{
		ft_putendl("Cylinder : out of bound value");
		free(o);
		return (NULL);
	}
	return (o);
}

/*
** Cylinder constructor
** Beware : cylinder radius is stored squared
** @return a pointer to a new struct cylinder, or null
*/

t_obj			*cylinder_new(char **t)
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
	o->param = o->param * o->param;
	o->color.r = (t_f)ft_atoi(*(t + 7)) * color_normalize;
	o->color.g = (t_f)ft_atoi(*(t + 8)) * color_normalize;
	o->color.b = (t_f)ft_atoi(*(t + 9)) * color_normalize;
	o->kspec = ft_atof(*(t + 10));
	o->kdiff = ft_atof(*(t + 11));
	o->kp = ft_atof(*(t + 12));
	o->intersect = &cylinder_intersect;
	o->normal = &cylinder_normal;
	return (check_cylinder(o));
}
