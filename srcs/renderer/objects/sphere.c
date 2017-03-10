/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:35:22 by vfour             #+#    #+#             */
/*   Updated: 2017/03/10 17:26:32 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** Intersection between ray and sphere
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/

int				sphere_intersect(t_obj *self, t_ray *ray)
{
	double		b;
	double		c;
	t_vec3		ray_sphere;

	ray_sphere = vec3_sub(ray->pos, self->pos);
	b = vec3_dot(ray_sphere, ray->dir);
	c = vec3_norm2(ray_sphere) - self->param;
	if (norm_quad_solve(b, c, &(ray->t)))
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
