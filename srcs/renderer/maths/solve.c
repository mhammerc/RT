/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:51:13 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 14:52:26 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

/*
** Solve a quadratic equation ax² + bx + c = 0
** Updates interval with new intersection distances and normal direction
** @return 1 if smaller solution found, 0 otherwise
*/

void		outwards_inwards_solve(t_interval *interval, double x1, double x2)
{
	if (x1 > 0)
	{
		interval->min[0].normal = OUTWARDS;
		interval->max[0].normal = INWARDS;
	}
	else if (x2 > 0)
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = INWARDS;
	}
	else
	{
		interval->min[0].normal = OUTWARDS;
		interval->max[0].normal = INWARDS;
	}
}

int			quad_solve(double a, double b, double c, t_interval *interval)
{
	double		d;
	double		x1;
	double		x2;

	d = b * b - 4.0 * a * c;
	if (d < 0.)
		return (0);
	d = sqrt(d);
	a = 0.5 / a;
	x1 = (-b - d) * a;
	x2 = (-b + d) * a;
	if (x1 > x2)
	{
		d = x1;
		x1 = x2;
		x2 = d;
	}
	if (x2 < 0)
		return (0);
	interval->min[0].dist = x1;
	interval->max[0].dist = x2;
	outwards_inwards_solve(interval, x1, x2);
	return (1);
}

/*
** Solve a quadratic equation ax² + bx + c = 0 with a == 1
** Updates interval with new intersection distances and normal direction
** @return 1 if smaller solution found, 0 otherwise
*/

int			norm_quad_solve(double b, double c, t_interval *interval)
{
	double		d;
	double		x1;
	double		x2;

	d = b * b - c;
	if (d < 0.)
	{
		return (0);
	}
	d = sqrt(d);
	x1 = -b - d;
	x2 = -b + d;
	if (x1 > x2)
	{
		d = x1;
		x1 = x2;
		x2 = d;
	}
	if (x2 < 0)
		return (0);
	interval->min[0].dist = x1;
	interval->max[0].dist = x2;
	outwards_inwards_solve(interval, x1, x2);
	return (1);
}
