/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_minus2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:17:04 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:17:05 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in substraction interval
*/

int		minus_case(t_interval *left, t_interval *right, t_interval *interval)
{
	if (left->nb_hit == 0)
	{
		interval->nb_hit = 0;
		return (0);
	}
	else if (right->nb_hit == 0)
	{
		*interval = *left;
		return (0);
	}
	return (1);
}

/*
**test kind intersection : total overlap
*/

int		minus_test0(t_interval *a_i, t_interval *a_j, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;

	min1 = a_i->min[i].dist;
	max1 = a_i->max[i].dist;
	min2 = a_j->min[j].dist;
	max2 = a_j->max[j].dist;
	if (min1 > min2 && max1 < max2)
		return (1);
	return (0);
}

int		minus_test00(t_interval *a_i, t_interval *a_j, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;

	min1 = a_i->min[i].dist;
	max1 = a_i->max[i].dist;
	min2 = a_j->min[j].dist;
	max2 = a_j->max[j].dist;
	if (min1 < min2 && max1 > max2)
		return (1);
	return (0);
}
