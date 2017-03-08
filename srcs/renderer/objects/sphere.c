/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:35:22 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 18:56:51 by vfour            ###   ########.fr       */
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

int				sphere_intersect(t_obj *self, t_ray *ray)
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

t_vec3			sphere_normal(t_obj *self, t_vec3 pos)
{
	return (vec3_get_normalized(vec3_sub(pos, self->pos)));
}
