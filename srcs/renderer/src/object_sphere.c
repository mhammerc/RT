/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:35:22 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:57:46 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Intersection between ray and sphere
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

static int		sphere_intersect(t_obj *self, t_ray *ray)
{
	t_f			b;
	t_f			c;
	t_vec3		ray_sphere;

	ray_sphere = vec3_sub(ray->pos, self->pos);
	b = vec3_dot(ray_sphere, ray->dir);
	c = vec3_norm2(ray_sphere) - self->param;
	if (normalized_quad_solve(b, c, &(ray->d)))
	{
		if (ray->type == INITIAL_RAY)
			ray->collided = self;
		return (1);
	}
	return (0);
}

/*
** Normal vector at given point
*/

static t_vec3	sphere_normal(t_obj *self, t_vec3 pos)
{
	return (vec3_get_normalized(vec3_sub(pos, self->pos)));
}

static t_obj	*check_sphere(t_obj *o)
{
	if (!float_checkbounds(o->color.r, 0, 1)
		|| !float_checkbounds(o->color.g, 0, 1)
		|| !float_checkbounds(o->color.b, 0, 1)
		|| !float_checkbounds(o->param, EPS, MAX_RADIUS)
		|| !float_checkbounds(o->kp, 0, MAX_KP)
		|| !float_checkbounds(o->kspec, 0, MAX_KSPEC)
		|| !float_checkbounds(o->kdiff, 0, MAX_KDIFF))
	{
		ft_putendl("Sphere : out of bound value");
		free(o);
		return (NULL);
	}
	return (o);
}

/*
** Sphere constructor
** Beware : sphere radius is stored squared
** @return a pointer to a new struct sphere, or null
*/

t_obj			*sphere_new(char **t)
{
	t_obj		*o;
	t_f			color_normalize;

	if (NULL == (o = (t_obj*)ft_memalloc(sizeof(t_obj))))
		ft_exit("Malloc error in Sphere constructor", EXIT_FAILURE);
	color_normalize = 1. / 255.;
	o->pos = (t_vec3){ft_atof(*t), ft_atof(*(t + 1)), ft_atof(*(t + 2))};
	o->param = ft_atof(*(t + 3));
	o->param = o->param * o->param;
	o->color.r = (t_f)ft_atoi(*(t + 4)) * color_normalize;
	o->color.g = (t_f)ft_atoi(*(t + 5)) * color_normalize;
	o->color.b = (t_f)ft_atoi(*(t + 6)) * color_normalize;
	o->kspec = ft_atof(*(t + 7));
	o->kdiff = ft_atof(*(t + 8));
	o->kp = ft_atof(*(t + 9));
	o->intersect = &sphere_intersect;
	o->normal = &sphere_normal;
	return (check_sphere(o));
}
