/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:01:37 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 16:20:11 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "shared.h"

t_vec3		vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3		vec3_cross(t_vec3 u, t_vec3 v)
{
	t_vec3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}

double		vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3		vec3_mult(double m, t_vec3 x)
{
	t_vec3	res;

	res.x = x.x * m;
	res.y = x.y * m;
	res.z = x.z * m;
	return (res);
}

t_vec3		vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
