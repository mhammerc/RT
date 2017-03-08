/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:00:02 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:00:38 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

/*
** Solve a quadratic equation ax² + bx + c
** root is replaced if a smaller solution is found
** @return 1 if smaller solution found, 0 otherwise
*/

int			quad_solve(t_f a, t_f b, t_f c, t_f *root)
{
	t_f		d;
	t_f		x1;
	t_f		x2;
	int		res;

	res = 0;
	d = b * b - 4.0 * a * c;
	if (d < 0.)
		return (0);
	d = sqrt(d);
	a = 0.5 / a;
	x1 = (-b - d) * a;
	x2 = (-b + d) * a;
	if (x1 > 0. && x1 < *root)
	{
		res = 1;
		*root = x1;
	}
	if (x2 > 0. && x2 < *root)
	{
		res = 1;
		*root = x2;
	}
	return (res);
}

/*
** Solve a quadratic equation ax² + bx + c with a == 1
** root is replaced if a smaller solution is found
** @return 1 if smaller solution found, 0 otherwise
*/

int			normalized_quad_solve(t_f b, t_f c, t_f *root)
{
	t_f		d;
	t_f		x1;
	t_f		x2;
	int		res;

	res = 0;
	d = b * b - c;
	if (d < 0.)
		return (0);
	d = sqrt(d);
	x1 = -b - d;
	x2 = -b + d;
	if (x1 > 0. && x1 < *root)
	{
		res = 1;
		*root = x1;
	}
	if (x2 > 0. && x2 < *root)
	{
		res = 1;
		*root = x2;
	}
	return (res);
}
