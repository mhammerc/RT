/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:16:12 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:16:13 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "renderer.h"

int				quad2_solve(long double b, long double c, long double *root)
{
	long double		d;

	d = b * b - 4. * c;
	if (d < 0.)
	{
		root[0] = BIG_DIST;
		root[1] = BIG_DIST;
		return (0);
	}
	d = sqrtl(d);
	root[0] = (-b - d) / 2.;
	root[1] = (-b + d) / 2.;
	return (1);
}

/*
** Solve a quadratic equation ax² + bx + c = 0 with a == 1
** Updates interval with new intersection distances and normal direction
** @return 1 if smaller solution found, 0 otherwise
*/

long double		case1(long double g, long double h,
		long double a, long double b)
{
	long double	r;
	long double s;
	long double	t;
	long double	u;

	t = -g / 2 - sqrtl(h);
	r = -g / 2. + sqrtl(h);
	if (r > 0)
		s = powl(r, 1. / 3.);
	else
		s = -powl(-r, 1. / 3.);
	if (t > 0)
		u = powl(t, 1. / 3.);
	else
		u = -powl(-t, 1. / 3.);
	return (s + u - b / (3 * a));
}

long double		case2(long double g, long double h,
		long double a, long double b)
{
	long double	i;
	long double	j;
	long double	k;

	i = sqrtl(powl(g, 2.) / 4 - h);
	j = powl(i, 1. / 3.);
	k = acosl(-g / (2. * i));
	return (2 * j * cosl(k / 3) - b / (3 * a));
}

long double		quad3_solve(long double a, long double b,
		long double c, long double d)
{
	long double	f;
	long double	g;
	long double	h;

	f = (3. * c / a - powl(b, 2.) / powl(a, 2.)) / 3;
	g = (2. * powl(b, 3.) / powl(a, 3.) - 9. * b * c
			/ powl(a, 2.) + 27 * d / a) / 27;
	h = powl(g, 2.) / 4. + powl(f, 3.) / 27.;
	if (h > 0.)
		return (case1(g, h, a, b));
	else if (f < EPS && g < EPS && f > EPS && g > EPS)
		return (powl(d / a, 1. / 3.));
	else
		return (case2(g, h, a, b));
}

int				quad4_solve(long double *a, t_interval *interval)
{
	long double y;
	long double	r_g[2];
	long double	r_h[2];
	long double tmp;

	y = quad3_solve(1, -a[1], a[0] * a[2] - 4 * a[3], -powl(a[0], 2) *
			a[3] - powl(a[2], 2) + 4 * a[1] * a[3]);
	if (!(quad2_solve(-a[0], a[1] - y, r_g)))
		return (0);
	if (!(quad2_solve(-y, a[3], r_h)))
		return (0);
	if (fabsl(r_g[0] * r_h[1] + r_g[1] * r_h[0] - a[2])
			> fabsl(r_g[0] * r_h[0] + r_g[1] * r_h[1] - a[2]))
	{
		tmp = r_h[0];
		r_h[0] = r_h[1];
		r_h[1] = tmp;
	}
	solve_interval(interval, r_g, r_h);
	return (interval->nb_hit);
}
