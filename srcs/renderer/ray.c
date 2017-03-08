/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:09:26 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 13:54:11 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

/*
** Ray constructor
** @return a new ray
*/

t_ray		ray_new_aim(t_vec3 pos, t_vec3 aim, t_color *col)
{
	t_vec3	dir;
	t_vec3	n;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, INITIAL_RAY, NULL, BIG_DIST + 1, col});
}
