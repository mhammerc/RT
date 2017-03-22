/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 08:34:15 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 08:36:14 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in intersecion interval
**
*/

int	inter_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0 || right->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (0);
	}
	return (1);
}

/*
**result in a_i : intersectin between interval *a_i and *a_j
**
*/

void	modify_by_inter(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_i->min[i].dist > a_j->min[j].dist)
	{
		a_i->min[i] = a_j->min[j];
		if (a_i->max[i].dist < a_j->max[j].dist)
			a_i->max[i] = a_j->max[j];
	}
}
/*
**result in interval : intersectin between all interval in right and left
**
*/

void	inter(t_interval *left, t_interval *right, t_interval *interval)
{
	int	l;
	int	r;
	int	i;

	if (!inter_case(left, right, interval))
		return;
	l = 0;
	i = 0;
	while (l < left->nb_hit)
	{
		interval->min[i] = left->min[l];
		interval->max[i] = left->max[l];
		r = 0;
		while (r < right->nb_hit)
		{
			if (is_disjoint(interval, right, i, r))
				break;
			else
				modify_by_inter(interval, right, i, r);
			r++;
		}
		if (r == right->nb_hit)
			i++;
		l++;
	}
	interval->nb_hit = i;
}

