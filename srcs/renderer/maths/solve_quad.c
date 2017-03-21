#include <math.h>
#include <stdio.h>
#include "renderer.h"

int			quad2_solve(long double b, long double c, long double *root)
{
	long double		d;

	d = b * b - 4. * c;
	if (d < 0.)
	{
		root[0] = 10000;
		root[1] = 10000;
		return (0);
	}
	d = sqrtl(d);
	root[0] = (-b - d) / 2.;
	root[1] = (-b + d) / 2.;
	return (1);
}

int			quad2_solve_inv(long double b, long double c, long double *root)
{
	long double		d;

	d = b * b - 4. * c;
	if (d < 0.)
		return (0);
	d = sqrtl(d);
	root[1] = (-b - d) / 2.;
	root[0] = (-b + d) / 2.;
	return (1);
}

/*
** Solve a quadratic equation ax² + bx + c = 0 with a == 1
** Updates interval with new intersection distances and normal direction
** @return 1 if smaller solution found, 0 otherwise
*/

long double			case1(long double g, long double h, long double a, long double b)
{
	long double	R = -g / 2. + sqrtl(h);
	long double S;
	if (R>0)
		S = powl(R, 1./3.);
	else
		S = -powl(-R, 1./3.);
	long double	T = -g / 2 - sqrtl(h);
	long double	U;
	if (T>0)
		U = powl(T, 1./3.);
	else
		U = -powl(-T, 1./3.);
	return(S + U - b / (3 * a));
}

long double			case2(long double g, long double h, long double a, long double b)
{
	long double	i = sqrtl(powl(g, 2.) / 4 - h);
	long double	j = powl(i, 1./3.);
	long double	K = acosl(-g /(2. * i));
		return(2* j * cosl(K / 3) - b / ( 3 *a));
}
long double			case3(long double g, long double h, long double a, long double b)
{
	long double	i = sqrtl(powl(g, 2.) / 4 - h);
	long double	j = powl(i, 1./3.);
	long double	k = acosl(-g /(2. * i));
	return(2* j * cosl(k / 3) - b / ( 3 *a));
}

long double			quad3_solve(long double a, long double b, long double c, long double d)
{
	long double	f = (3. * c / a - powl(b, 2.) / powl(a, 2.)) / 3;
	long double	g = (2. * powl(b, 3.) / powl(a, 3.) - 9. * b * c / powl(a, 2.) + 27 * d / a) / 27;
	long double	h = powl(g, 2.) / 4. + powl(f, 3.) / 27.;
	if ( h > 0.)
		return (case1(g, h, a, b));
	else if (f < EPS && g < EPS && f > EPS && g > EPS)
		return(powl(d / a, 1. / 3.));
	else
	{
		return (case2(g, h, a, b));
	}
}
int		quad4_solve(long double a, long double b, long double c, long double d, t_interval *interval)
{
	long double y = quad3_solve(1, -b,a * c - 4 *d,-powl(a,2) * d - powl(c,2) + 4 * b * d);
	long double	r_g[2];
	long double	r_h[2];
	if(!(quad2_solve(-a, b - y, r_g)))
		return (0);
	if(!(quad2_solve(-y, d, r_h)))
		return (0);
	if (fabsl(r_g[0] * r_h[1] + r_g[1] * r_h[0] - c) > fabsl(r_g[0] * r_h[0] + r_g[1] * r_h[1] - c))
		{
			long double	tmp = r_h[0];
			r_h[0] = r_h[1];
			r_h[1] = tmp;
		}
	long double	root_1[2];
	long double	root_2[2];
	interval->nb_hit = 0;
	if (quad2_solve(r_g[0], r_h[0], root_1))
	{
		if (quad2_solve(r_g[1], r_h[1], root_2))
		{
			interval->nb_hit = 2;
			if (root_1[0] < root_2[0])
			{
				interval->min[0].dist = root_1[0];
				interval->min[0].normal = OUTWARDS;
				interval->max[0].normal = INWARDS;
				interval->min[1].normal = OUTWARDS;
				interval->max[1].normal = INWARDS;
				if (root_1[1] < root_2[0])
				{
					interval->max[0].dist = root_1[1];
					interval->min[1].dist = root_2[0];
					interval->max[1].dist = root_2[1];
				}
				else if (root_1[1] < root_2[1])
				{
					interval->max[0].dist = root_2[0];
					interval->min[1].dist = root_1[1];
					interval->max[1].dist = root_2[1];
				}
				else
				{
					interval->max[0].dist = root_2[0];
					interval->min[1].dist = root_2[1];
					interval->max[1].dist = root_1[1];
				}
			}
			else
			{
				interval->min[0].dist = root_2[0];
				if (root_2[1] < root_1[0])
				{
					interval->max[0].dist = root_2[1];
					interval->min[1].dist = root_1[0];
					interval->max[1].dist = root_1[1];
				}
				else if (root_2[1] < root_1[1])
				{
					interval->max[0].dist = root_1[0];
					interval->min[1].dist = root_2[1];
					interval->max[1].dist = root_1[1];
				}
				else
				{
					interval->max[0].dist = root_1[0];
					interval->min[1].dist = root_1[1];
					interval->max[1].dist = root_2[1];
				}
			}
		}
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
	return (interval->nb_hit);
}
