/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:01:37 by vfour             #+#    #+#             */
/*   Updated: 2017/02/25 23:22:46 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "env.h"

FLOAT3	vec3_add(FLOAT3 a, FLOAT3 b)
{
	return ((FLOAT3){a.x + b.x, a.y + b.y, a.z + b.z});
}

FLOAT3	vec3_cross(FLOAT3 u, FLOAT3 v)
{
	return ((FLOAT3){u.y * v.z - u.z * v.y,
					u.z * v.x - u.x * v.z,
					u.x * v.y - u.y * v.x});
}

FLOAT	vec3_dot(FLOAT3 a, FLOAT3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

FLOAT3	vec3_mult(FLOAT m, FLOAT3 x)
{
	return ((FLOAT3){x.x * m, x.y * m, x.z * m});
}

FLOAT3	vec3_sub(FLOAT3 a, FLOAT3 b)
{
	return ((FLOAT3){a.x - b.x, a.y - b.y, a.z - b.z});
}
