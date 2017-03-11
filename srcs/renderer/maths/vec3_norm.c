/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:48:57 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 16:20:36 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "renderer.h"
#include "shared.h"

void		vec3_normalize(t_vec3 *v)
{
	double	invnorm;

	invnorm = 1.0 / vec3_norm(*v);
	v->x *= invnorm;
	v->y *= invnorm;
	v->z *= invnorm;
}

t_vec3		vec3_get_normalized(t_vec3 v)
{
	double	invnorm;
	t_vec3	res;

	invnorm = 1.0 / vec3_norm(v);
	res.x = v.x * invnorm;
	res.y = v.y * invnorm;
	res.z = v.z * invnorm;
	return (res);
}

double		vec3_norm2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double		vec3_norm(t_vec3 v)
{
	return ((double)sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
