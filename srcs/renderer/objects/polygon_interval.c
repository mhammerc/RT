/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_interval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:18:08 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:18:09 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <libft.h>
#include "renderer.h"

void		sort_interval(t_interval *interval, int i, t_csg swap, int cmp)
{
	t_csg	tmp;
	int		nb;

	nb = interval->nb_hit - 1;
	while (i < nb)
	{
		tmp = interval->max[i];
		interval->max[i] = interval->min[i];
		interval->min[i] = swap;
		swap = tmp;
		i++;
	}
	if (cmp % 2)
	{
		interval->max[i] = interval->min[i];
		interval->min[i] = swap;
	}
	else
	{
		interval->min[i] = swap;
		interval->max[i] = swap;
	}
}

void		sort_interval_case1(t_interval *interval, int i, t_csg tmp, int cmp)
{
	t_csg	swap;

	swap = interval->max[i];
	interval->max[i] = interval->min[i];
	interval->min[i] = tmp;
	sort_interval(interval, i + 1, swap, cmp);
}

void		sort_interval_case2(t_interval *interval, int i, t_csg tmp, int cmp)
{
	t_csg	swap;

	swap = interval->max[i];
	interval->max[i] = tmp;
	sort_interval(interval, i + 1, swap, cmp);
}

int			adapt_polygon2csg_init(t_interval *interval, t_csg t,
		int *cmp, double *tmp)
{
	int		i;
	int		nb;

	nb = interval->nb_hit - 1;
	i = 0;
	*tmp = t.dist;
	while (i < nb)
	{
		if (*tmp < interval->min[i].dist)
		{
			sort_interval_case1(interval, i, t, *cmp);
			break ;
		}
		else if (*tmp < interval->max[i].dist)
		{
			sort_interval_case2(interval, i, t, *cmp);
			break ;
		}
		i++;
	}
	return (i);
}

void		adapt_polygon2csg(t_interval *interval, t_csg t, int *cmp)
{
	int		i;
	int		nb;
	double	tmp;

	if (*cmp % 2 == 0)
		interval->nb_hit++;
	nb = interval->nb_hit - 1;
	i = adapt_polygon2csg_init(interval, t, cmp, &tmp);
	if (i == nb)
	{
		if (*cmp % 2 == 0)
		{
			interval->min[i] = t;
			interval->max[i] = t;
		}
		else if (tmp < interval->min[i].dist)
		{
			interval->max[i] = interval->min[i];
			interval->min[i] = t;
		}
		else
			interval->max[i] = t;
	}
	(*cmp)++;
}
