/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:48:57 by vfour             #+#    #+#             */
/*   Updated: 2017/02/26 01:04:47 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "env.h"

void		vec3_normalize(FLOAT3 *v)
{
	FLOAT	invnorm;

	invnorm = 1.0 / vec3_norm(*v);
	v->x *= invnorm;
	v->y *= invnorm;
	v->z *= invnorm;
}

FLOAT3		vec3_get_normalized(FLOAT3 v)
{
	FLOAT	invnorm;
	FLOAT3	res;

	invnorm = 1.0 / vec3_norm(v);
	res.x = v.x * invnorm;
	res.y = v.y * invnorm;
	res.z = v.z * invnorm;
	return (res);
}

FLOAT		vec3_norm2(FLOAT3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

FLOAT		vec3_norm(FLOAT3 v)
{
	return ((FLOAT)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
