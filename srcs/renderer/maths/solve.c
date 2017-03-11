#include <math.h>
#include "renderer.h"

/*
** Solve a quadratic equation ax² + bx + c = 0
** root is replaced if a smaller solution is found
** @return 1 if smaller solution found, 0 otherwise
*/

int			quad_solve(double a, double b, double c, double *root)
{
	double		d;
	double		x1;
	double		x2;
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

int			quad_solve2(double a, double b, double c, t_interval *interval)
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
	if (x1 > 0)
	{
		interval->min[0].normal = 0;
		interval->max[0].normal = 1;
	}
	else
	{
		interval->min[0].normal = 1;
		interval->max[0].normal = 0;
	}
		return (1);
}

/*
** Solve a quadratic equation ax² + bx + c = 0
** with a == 1
** root is replaced if a smaller solution is found
** @return 1 if smaller solution found, 0 otherwise
*/

int			norm_quad_solve(double b, double c, double *root)
{
	double		d;
	double		x1;
	double		x2;
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

int			norm_quad_solve2(double b, double c, t_interval *interval)
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
	if (x1 > 0)
	{
		interval->min[0].normal = 0;
		interval->max[0].normal = 1;
	}
	else
	{
		interval->min[0].normal = 1;
		interval->max[0].normal = 0;
	}
		return (1);
}
