/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:48:57 by vfour             #+#    #+#             */
/*   Updated: 2017/02/25 23:34:37 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "env.h"

void	vec3_normalize(FLOAT3 *v)
{
	FLOAT	invnorm;

	invnorm = 1.0 / vec3_norm(*v);
	v->x *= invnorm;
	v->y *= invnorm;
	v->z *= invnorm;
}

FLOAT3	vec3_get_normalized(FLOAT3 v)
{
	FLOAT	invnorm;

	invnorm = 1.0 / vec3_norm(v);
	return ((FLOAT3){v.x * invnorm, v.y * invnorm, v.z * invnorm});
}

FLOAT	vec3_norm2(FLOAT3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

FLOAT	vec3_norm(FLOAT3 v)
{
	return ((FLOAT)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
