#include <math.h>
#include <stdio.h>
#include "renderer.h"

int			quad2_solve(long double b, long double c, long double *root)
{
	long double	d;

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
	long double	R = -g / 2. + sqrt(h);
	long double S;
	if (R>0)
		S = pow(R, 1./3.);
	else
		S = -pow(-R, 1./3.);
	long double	T = -g / 2 - sqrt(h);
	long double	U;
	if (T>0)
		U = pow(T, 1./3.);
	else
		U = -pow(-T, 1./3.);
	return(S + U - b / (3 * a));
}

long double			case2(long double g, long double h, long double a, long double b)
{
	long double	i = sqrt(pow(g, 2.) / 4 - h);
	long double	j = pow(i, 1./3.);
	long double	K = acos(-g /(2. * i));
		return(2* j * cos(K / 3) - b / ( 3 *a));
}
long double			case3(long double g, long double h, long double a, long double b)
{
	long double	i = sqrt(pow(g, 2.) / 4 - h);
	long double	j = pow(i, 1./3.);
	long double	k = acos(-g /(2. * i));
	return(2* j * cos(k / 3) - b / ( 3 *a));
}

long double			quad3_solve(long double a, long double b, long double c, long double d)
{
	long double	f = (3. * c / a - pow(b, 2.) / pow(a, 2.)) / 3;
	long double	g = (2. * pow(b, 3.) / pow(a, 3.) - 9. * b * c / pow(a, 2.) + 27 * d / a) / 27;
	long double	h = pow(g, 2.) / 4. + pow(f, 3.) / 27.;
	if ( h > 0.)
		return (case1(g, h, a, b));
	else if (f < EPS && g < EPS && f > EPS && g > EPS)
		return(pow(d / a, 1. / 3.));
	else
	{
		return (case2(g, h, a, b));
	}
}
int		quad4_solve(long double a, double b, double c, double d, t_interval *interval)
{
	double y = quad3_solve(1, -b,a * c - 4 *d,-pow(a,2) * d - pow(c,2) + 4 * b * d);
	double	r_g[2];
	double	r_h[2];
	if(!(quad2_solve(-a, b - y, r_g)))
		return (0);
	if(!(quad2_solve(-y, d, r_h)))
		return (0);
	if (fabs(r_g[0] * r_h[1] + r_g[1] * r_h[0] - c) > fabs(r_g[0] * r_h[0] + r_g[1] * r_h[1] - c))
		{
			double	tmp = r_h[0];
			r_h[0] = r_h[1];
			r_h[1] = tmp;
		}
	double	root_1[2];
	double	root_2[2];
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
	/*	//printf("not 2\n");
	//printf("x1 %f x2 %f x3 %f x4 %f\n", root_1[0], root_1[1], root_2[0], root_2[1]);

	double	root;
	if ( root_1[0] > 0 && root_1[0] < root_1[1] && root_1[0] < root_2[0] && root_1[0] < root_2[1] )
		root = root_1[0];
	else if ( root_1[1] > 0 && root_1[1] < root_1[0] && root_1[1] < root_2[0] && root_1[1] < root_2[1] )
		root = root_1[1];
	else if ( root_2[0] > 0 && root_2[0] < root_1[0] && root_2[0] < root_1[1] && root_2[0] < root_2[1] )
		root = root_2[0];
	else if ( root_2[1] > 0 && root_2[1] < root_1[0] && root_2[1] < root_1[1] && root_2[1] < root_2[0] )
		root = root_2[1];
	else
		return (0);
	//printf("x^4+ %fx^3 + %fx^2 +%fx + %f\n",a,b,c,d);
	//printf("x1 %f x2 %f x3 %f x4 %f\n" ,root_1[0], root_1[1], root_2[0], root_2[1]);
	interval->min[0].dist.dist = root;
	interval->max[0].dist.dist = root;
	if (root > 0)
	{
		interval->min[0].dist.normal = OUTWARDS;
		interval->max[0].dist.normal = INWARDS;
	}
	else
	{
		interval->min[0].dist.normal = INWARDS;
		interval->max[0].dist.normal = OUTWARDS;
	}
	return (1);
	*/
}
/*
int			quad4_solve(double a, double b, double c, double d, double e, t_interval *interval)
{
	int			nb_root;
	double		x1;
	double		x2;
	double		x3;
	double		x4;
	double		e3 = pow(e, 3.);
	double		e2 = pow(e, 2.);
	double		c2 = pow(c, 2.);
	double		c3 = pow(c, 3.);
	double		c4 = pow(c, 4.);
	double		d2 = pow(d, 2.);
	double		d3 = pow(d, 3.);
	double		d4 = pow(d, 4.);
	double		b2 = pow(b, 2.);
	double		b3 = pow(b, 3.);
	double		b4 = pow(b, 4.);

	double		delta0 = c2 - 3. *b*d + 12. *e;
	double		delta1 = 2. * c3 - 9. * b* c*d +27. *b2*e +27.*d2 -72.*c*e;
	double	p = (8. *c - 3.*b2)/8.;
	double q = (b3 - 4. *b*c+ 8. *d)/ 8.;
	double	delta = 27 * (4. * pow(delta0, 3.) - pow(delta1, 2.));
	double	P = 8 * c - 3 * b2;
	double	L = b3 + 8*d - 4 * b *c;
	double	D = 64 * e - 16 * c2 + 16 *b2 * c - 16 *b *d - 3 * b4;
	if ( D < EPS && D > -EPS)
		//printf("4 root\n");



	double S;
	double phi;
	double tmp0;
	if (delta > 0)
	{
		if ( P > 0 && D < 0)
			return (0);
//		if (delta0 < 0)
//			return (0);
		phi = acos ( delta1 / ( 2. * pow (delta0, 3.)));
		if ((tmp0 = -2. * p / 3. + 2. * sqrt(delta0) * cos (phi / 3.) / 3.) < 0)
			;
			//return (0);
		S = sqrt(tmp0) / 2.;
	}
	else
	{
	double Q = pow( (delta1 + sqrt(delta1 * delta1 - 4. * delta0 * delta0 * delta0)) / 2., 1.0 / 3.0);
	if ( Q < EPS && Q > -EPS)
	{
		//printf("Q negatif\n");
		return (0);
	}
	double	titi = -2. * p /3. + (Q + delta0 / Q)/3.;
	if (titi < 0)
		return (0);
	S = sqrt(titi)/ 2;
	}
	nb_root = 4;
	double	tmp1 = -4. * pow (S, 2.) - 2. *p + q / S;
	if(tmp1 >= 0)
	{
		x1 = -b/4. - S + sqrt(tmp1)/2;
		x2 = -b/4. - S - sqrt(tmp1)/2;
	}
	else
	{
		nb_root -=2;
		x1 = 10000;
		x2 = 10000;
	}
	double	tmp2 = -4. * pow (S, 2.) - 2. *p - q/S;
	if(tmp2 >= 0)
	{
		x3 = -b/4. + S + sqrt(tmp2)/2;
		x4 = -b/4. + S - sqrt(tmp2)/2;
	}
	else
	{
		nb_root -=2.;
		x3 = 10000;
		x4 = 10000;
	}
	if (!nb_root)
		return (0);
	double	root;
	if ( x1 > 0 && x1 < x2 && x1 < x3 && x1 < x4 )
		root = x1;
	if ( x2 > 0 && x2 < x1 && x2 < x3 && x2 < x4 )
		root = x2;
	if ( x3 > 0 && x3 < x1 && x3 < x2 && x3 < x4 )
		root = x3;
	if ( x4 > 0 && x4 < x1 && x4 < x2 && x4 < x3 )
		root = x4;
	interval->min[0].dist.dist = root;
	interval->max[0].dist.dist = root;
	if (root > 0)
	{
		interval->min[0].dist.normal = OUTWARDS;
		interval->max[0].dist.normal = INWARDS;
	}
	else
	{
		interval->min[0].dist.normal = INWARDS;
		interval->max[0].dist.normal = OUTWARDS;
	}
	return (1);
}
*/
