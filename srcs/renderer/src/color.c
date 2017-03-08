/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:52:07 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:12:24 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rtv1.h"

int			colorcomp_to_rgb(int r, int g, int b)
{
	r = r < 0 ? 0 : (r & 0xff);
	g = g < 0 ? 0 : (g & 0xff);
	b = b < 0 ? 0 : (b & 0xff);
	return ((r << 16) + (g << 8) + b);
}

/*
** Add color components
*/

void		color_add_light(t_ray ray, t_light *l, t_vec3 obj_cam)
{
	t_color	*c;
	t_color	obj;
	t_f		diff;
	t_vec3	h;

	c = ray.col;
	obj = ray.collided->color;
	if ((diff = fmax(vec3_dot(ray.dir, ray.n), 0)) > 0)
	{
		diff = diff * ray.collided->kdiff * l->i;
		c->r += l->color.r * obj.r * diff;
		c->g += l->color.g * obj.g * diff;
		c->b += l->color.b * obj.b * diff;
	}
	h = vec3_get_normalized(vec3_add(obj_cam, ray.dir));
	if ((diff = fmax(pow(vec3_dot(ray.n, h), ray.collided->kp), 0)) > 0)
	{
		diff = diff * ray.collided->kspec * l->i;
		c->r += l->color.r * obj.r * diff;
		c->g += l->color.g * obj.g * diff;
		c->b += l->color.b * obj.b * diff;
	}
}

void		color_add_ambiant(t_color *c, t_color obj, t_light ambiant)
{
	c->r += ambiant.color.r * obj.r * ambiant.i;
	c->g += ambiant.color.g * obj.g * ambiant.i;
	c->b += ambiant.color.b * obj.b * ambiant.i;
}
