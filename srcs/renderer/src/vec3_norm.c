/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:48:57 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:29:41 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

t_f		vec3_norm(t_vec3 v)
{
	return ((t_f)sqrt(vec3_norm2(v)));
}

void	vec3_normalize(t_vec3 *v)
{
	t_f	invnorm;

	invnorm = 1.0 / vec3_norm(*v);
	v->x *= invnorm;
	v->y *= invnorm;
	v->z *= invnorm;
}

t_vec3	vec3_get_normalized(t_vec3 v)
{
	t_f	invnorm;

	invnorm = 1.0 / vec3_norm(v);
	return ((t_vec3){v.x * invnorm, v.y * invnorm, v.z * invnorm});
}

t_f		vec3_norm2(t_vec3 v)
{
	return (vec3_dot(v, v));
}
