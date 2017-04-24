/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_positiv_dist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:15:56 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:15:59 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

int			modify_ref_dist(double *d, t_obj **collided,
		t_csg inter, t_obj *obj)
{
	ft_memcpy(*collided, &(inter.ref), sizeof(t_obj));
	*d = inter.dist;
	obj->csg_ref = *collided;
	obj->csg_ref->normal_dir = inter.normal;
	return (1);
}

/*
** fill distance minimal positive and ref_obj
** @return 0 if no distance 1 else
*/

int			minimal_positiv(t_interval *interval, t_obj *obj,
		double *d, t_obj **collided)
{
	int		i;
	int		hit;
	int		location;

	location = LOCATION_NONE;
	if (interval->nb_hit == 0)
		return (LOCATION_NONE);
	i = 0;
	while (i < interval->nb_hit)
	{
		hit = 0;
		if (*d > interval->min[i].dist && interval->min[i].dist > 0)
			hit = modify_ref_dist(d, collided, interval->min[i], obj);
		if (*d > interval->max[i].dist && interval->max[i].dist > 0)
			hit = modify_ref_dist(d, collided, interval->max[i], obj);
		if (hit)
		{
			if (0 > interval->min[i].dist && 0 < interval->max[i].dist)
				location = LOCATION_INSIDE;
			else
				location = LOCATION_OUTSIDE;
		}
		i++;
	}
	return (location);
}
