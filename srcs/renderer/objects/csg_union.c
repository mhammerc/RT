/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_union.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:28:17 by racousin          #+#    #+#             */
/*   Updated: 2017/03/21 17:47:36 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in union interval
**
*/

int	union_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0 && right->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (1);
	}
	if (left->nb_hit == 0)
	{
		*interval = *right;
		return (1);
	}
	if (right->nb_hit == 0)
	{
		*interval = *left;
		return (1);
	}
	return (0);
}

/*
**
**modify : union between a_i and a_j put in a_i
*/
void	modify_by_union(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_j->min[j].dist < a_i->min[i].dist)
		a_i->min[i] = a_j->min[j];
	if (a_j->max[j].dist > a_i->max[i].dist)
		a_i->max[i] = a_j->max[j];
}

/*
**
**result in interval : left union right
*/
void	ft_union(t_interval *left, t_interval *right, t_interval *interval)
{
	int	i;
	int	j;
	int	test[10];

	if (union_case(left, right, interval))
		return;
	i = 0;
	while (i < right->nb_hit)
	{
		left->min[i + left->nb_hit] = right->min[i];
		left->max[i + left->nb_hit] = right->max[i];
		test[i] = 1;
		i++;
	}
	while (i < left->nb_hit + right->nb_hit)
		test[i++] = 1;
	while (i < 10)
		test[i++] = 0;
	i = 0;
	while (i < 9)
	{
		j = i + 1;
		while (j < 10)
		{
			if (test[j])
			{
				if (!is_disjoint(left, left, i, j))
				{
					modify_by_union(left, left, i, j);
					test[j] = 0;
					j = i;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (j < 10)
	{
		if (test[j])
		{
			interval->min[i] = left->min[j];
			interval->max[i] = left->max[j];
			i++;
		}
		j++;
	}
	interval->nb_hit = i;
}
