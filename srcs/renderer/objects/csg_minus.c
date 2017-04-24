/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_minus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:16:57 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:16:57 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** modify : creat new segment
*/

void	modify_by_minus2(t_interval *a_i, t_interval *a_j,
		int *l, t_interval *a_h)
{
	int	i;
	int	*j;

	i = l[2];
	j = l + 1;
	a_i->min[i + 1] = a_j->max[*j];
	a_i->max[i + 1] = a_i->max[i];
	a_i->max[i] = a_j->min[*j];
	(*j)++;
	i++;
	a_h->min[a_h->nb_hit] = a_i->min[i];
	a_h->max[a_h->nb_hit] = a_i->max[i];
	if (a_h->nb_hit < 20)
		(a_h->nb_hit)++;
}

/*
**modify : eat a_j in a_i
*/

void	modify_by_minus1(t_interval *a_i, t_interval *a_j, int i, int *j)
{
	if (a_i->min[i].dist < a_j->min[*j].dist)
		a_i->max[i] = a_j->min[*j];
	else
		a_i->min[i] = a_j->max[*j];
	(*j)++;
}

/*
**result in interval : left minus right
*/

int		init_minus(t_interval *interval, t_interval *left, int l2, int l0)
{
	interval->min[l2] = left->min[l0];
	interval->max[l2] = left->max[l0];
	return (0);
}

void	minus(t_interval *left, t_interval *right, t_interval *interval)
{
	int	l[3];

	if (!(minus_case(left, right, interval)))
		return ;
	l[0] = -1;
	l[2] = 0;
	while (++l[0] < left->nb_hit)
	{
		l[1] = init_minus(interval, left, l[2], l[0]);
		while (l[1] < right->nb_hit)
		{
			if (is_disjoint(interval, right, l[2], l[1]))
				l[1]++;
			else if (minus_test0(interval, right, l[2], l[1]))
				break ;
			else if (minus_test00(interval, right, l[2], l[1]))
				modify_by_minus2(interval, right, l, left);
			else
				modify_by_minus1(interval, right, l[2], l + 1);
		}
		if (l[1] == right->nb_hit)
			l[2]++;
	}
	interval->nb_hit = l[2];
}
