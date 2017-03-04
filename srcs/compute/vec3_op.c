/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:01:37 by vfour             #+#    #+#             */
/*   Updated: 2017/02/26 01:04:45 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "env.h"

FLOAT3		vec3_add(FLOAT3 a, FLOAT3 b)
{
	FLOAT3	res;
	
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

FLOAT3		vec3_cross(FLOAT3 u, FLOAT3 v)
{
	FLOAT3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}

FLOAT		vec3_dot(FLOAT3 a, FLOAT3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

FLOAT3		vec3_mult(FLOAT m, FLOAT3 x)
{
	FLOAT3	res;
	
	res.x = x.x * m;
	res.y = x.y * m;
	res.z = x.z * m;
	return (res);
}

FLOAT3		vec3_sub(FLOAT3 a, FLOAT3 b)
{
	FLOAT3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
