/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_union.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:17:10 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:17:11 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in union interval
*/

int		union_case(t_interval *left, t_interval *right, t_interval *interval)
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
	if (right->nb_hit == 0 || right->nb_hit + left->nb_hit > 20)
	{
		*interval = *left;
		return (1);
	}
	return (0);
}

/*
**modify : union between a_i and a_j put in a_i
*/

void	modify_by_union(t_interval *a_i, t_interval *a_j, int i, int j)
{
	if (a_j->min[j].dist < a_i->min[i].dist)
		a_i->min[i] = a_j->min[j];
	if (a_j->max[j].dist > a_i->max[i].dist)
		a_i->max[i] = a_j->max[j];
}

void	init_union(t_interval *left, t_interval *right, int *test)
{
	int	i;

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
	while (i < 20)
		test[i++] = 0;
}

void	fill_interval_complete(t_interval *interval,
		t_interval *left, int *test)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 20)
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

/*
**result in interval : left union right
*/

void	ft_union(t_interval *left, t_interval *right, t_interval *interval)
{
	int	i;
	int	j;
	int	test[20];

	if (union_case(left, right, interval))
		return ;
	init_union(left, right, test);
	i = -1;
	while (++i < 19)
	{
		j = i;
		while (++j < 20)
		{
			if (test[j])
				if (!is_disjoint(left, left, i, j))
				{
					modify_by_union(left, left, i, j);
					test[j] = 0;
					j = i;
				}
		}
	}
	fill_interval_complete(interval, left, test);
}
