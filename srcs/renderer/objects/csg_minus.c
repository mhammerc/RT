/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_minus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 08:36:22 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 08:37:52 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

/*
** particulary case solve quickly in substraction interval
**
*/

int	minus_case(t_interval *left, t_interval *right, t_interval *interval)
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
**
**test kind intersection : partiel overlap
*/

int	minus_test1(t_interval *a_i, t_interval *a_j, int i, int j)
{
	double	min1;
	double	min2;
	double	max1;
	double	max2;
	
	min1 = a_i->min[i].dist;
	max1 = a_i->max[i].dist;
	min2 = a_j->min[j].dist;
	max2 = a_j->max[j].dist;
	if (min1 < min2 && max1 < min2)
		return (0);
	if (min2 < min1 && max2 < min1)
		return (0);
	return (1);
}
/*
**
**test kind intersection : total overlap
*/
int	minus_test0(t_interval *a_i, t_interval *a_j, int i, int j)
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

int	minus_test00(t_interval *a_i, t_interval *a_j, int i, int j)
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
/*
**
** modify : creat new segment
*/
void	modify_by_minus2(t_interval *a_i, t_interval *a_j, int i, int *j)
{
	a_i->min[i + 1] = a_j->max[*j];
	a_i->max[i + 1] = a_i->max[i];
	a_i->max[i] = a_j->min[*j];
	(*j)++;
}
void	modify_by_minus3(t_interval *a_i, t_interval *a_j, int i)
{
	a_j->min[a_j->nb_hit] = a_i->min[i];
	a_j->max[a_j->nb_hit] = a_i->max[i];
	(a_j->nb_hit)++;
}

/*
**
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
**
**result in interval : left minus right
*/

void	minus(t_interval *left, t_interval *right, t_interval *interval)
{
	int	l;
	int	r;
	int	i;

	if (!(minus_case(left, right, interval)))	
		return;
	l = 0;
	i = 0;
	while (l < left->nb_hit)
	{
			//	printf("what0 l %d\n",l);
		interval->min[i] = left->min[l];
		interval->max[i] = left->max[l];
		r = 0;
		while (r < right->nb_hit)
		{
			//	printf("boucle right\n");
			if (is_disjoint(interval, right, i, r))
			{
			//	printf("disjoint i %d\n", i);
				r++;
			}
			else if (minus_test0(interval, right, i, r))
			{
				//printf("ecrasement\n");
				break;
			}
			else if (minus_test00(interval, right, i, r))
			{
				modify_by_minus2(interval, right, i, &r);
				modify_by_minus3(interval, left, i + 1);
			}
			else //if (minus_test1(interval, right, i, r))
			{
			//	printf("chevauchement\n");
				modify_by_minus1(interval, right, i, &r);
			}
		}
		if  (r == right->nb_hit)
			i++;
		l++;
				//printf("i %d\n", i);
	}
	interval->nb_hit = i;
}
