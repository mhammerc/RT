/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quad_2_interval.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:16:05 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:16:07 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "renderer.h"

void	solve2interval0(t_interval *interval, double max0,
		double min1, double max1)
{
	interval->max[0].dist = max0;
	interval->min[1].dist = min1;
	interval->max[1].dist = max1;
}

void	case_fct(t_interval *interval, long double *root_1, long double *root_2)
{
	interval->nb_hit = 2;
	if (root_1[0] < root_2[0])
	{
		interval->min[0].dist = root_1[0];
		if (root_1[1] < root_2[0])
			solve2interval0(interval, root_1[1], root_2[0], root_2[1]);
		else if (root_1[1] < root_2[1])
			solve2interval0(interval, root_2[0], root_1[1], root_2[1]);
		else
			solve2interval0(interval, root_2[0], root_2[1], root_1[1]);
	}
	else
	{
		interval->min[0].dist = root_2[0];
		if (root_2[1] < root_1[0])
			solve2interval0(interval, root_2[1], root_1[0], root_1[1]);
		else if (root_2[1] < root_1[1])
			solve2interval0(interval, root_1[0], root_2[1], root_1[1]);
		else
			solve2interval0(interval, root_1[0], root_2[1], root_2[1]);
	}
}

void	outwards_inwards2(t_interval *interval)
{
	if (interval->min[1].dist > 0)
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
		interval->min[1].normal = OUTWARDS;
		interval->max[1].normal = INWARDS;
	}
	else if (interval->max[1].dist > 0)
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
		interval->min[1].normal = INWARDS;
		interval->max[1].normal = INWARDS;
	}
	else
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
		interval->min[1].normal = INWARDS;
		interval->max[1].normal = OUTWARDS;
	}
}

void	outwards_inwards(t_interval *interval)
{
	if (interval->min[0].dist > 0)
	{
		interval->min[0].normal = OUTWARDS;
		interval->max[0].normal = INWARDS;
		interval->min[1].normal = OUTWARDS;
		interval->max[1].normal = INWARDS;
	}
	else if (interval->max[0].dist > 0)
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = INWARDS;
		interval->min[1].normal = OUTWARDS;
		interval->max[1].normal = INWARDS;
	}
	else if (interval->nb_hit == 1)
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
	}
	else
		outwards_inwards2(interval);
}

void	solve_interval(t_interval *interval, long double *r_g, long double *r_h)
{
	long double	root_1[2];
	long double	root_2[2];

	interval->nb_hit = 0;
	if (quad2_solve(r_g[0], r_h[0], root_1))
	{
		if (quad2_solve(r_g[1], r_h[1], root_2))
			case_fct(interval, root_1, root_2);
		else
		{
			interval->nb_hit = 1;
			interval->min[0].dist = root_1[0];
			interval->max[0].dist = root_1[1];
		}
	}
	else if (quad2_solve(r_g[1], r_h[1], root_2))
	{
		interval->nb_hit = 1;
		interval->min[0].dist = root_2[0];
		interval->max[0].dist = root_2[1];
	}
	if (interval->nb_hit)
		outwards_inwards(interval);
}
