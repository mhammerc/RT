/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:09:33 by racousin          #+#    #+#             */
/*   Updated: 2017/03/18 18:14:37 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "renderer.h"

int			quad2_solve(double b, double c, double *root)
{
	double		d;

	d = b * b - 4. * c;
	if (d < 0.)
	{
		root[0] = 10000;
		root[1] = 10000;
		return (0);
	}
	d = sqrt(d);
	root[0] = (-b - d) / 2.;
	root[1] = (-b + d) / 2.;
	return (1);
}

int			quad2_solve_inv(double b, double c, double *root)
{
	double		d;

	d = b * b - 4. * c;
	if (d < 0.)
		return (0);
	d = sqrt(d);
	root[1] = (-b - d) / 2.;
	root[0] = (-b + d) / 2.;
	return (1);
}

/*
** Solve a quadratic equation ax² + bx + c = 0 with a == 1
** Updates interval with new intersection distances and normal direction
** @return 1 if smaller solution found, 0 otherwise
*/

double			case1(double g, double h, double a, double b)
{
	double	R = -g / 2. + sqrt(h);
	double S;
	if (R>0)
		S = pow(R, 1./3.);
	else
		S = -pow(-R, 1./3.);
	double	T = -g / 2 - sqrt(h);
	double	U;
	if (T>0)
		U = pow(T, 1./3.);
	else
		U = -pow(-T, 1./3.);
	return(S + U - b / (3 * a));
}

double			case2(double g, double h, double a, double b)
{
	double	i = sqrt(pow(g, 2.) / 4 - h);
	double	j = pow(i, 1./3.);
	double	K = acos(-g /(2. * i));
		return(2* j * cos(K / 3) - b / ( 3 *a));
//	double	L = -j;
//	double	M = cos(K / 3.);
//	double	N = 1.73205 * sin(K / 3);
//	double	P = -b / (3 * a);
//	if (root_number == 1)
//		return (L * (M + N) + P);
//	else
//		return (L * (M - N) + P);
}
double			case3(double g, double h, double a, double b)
{
	double	i = sqrt(pow(g, 2.) / 4 - h);
	double	j = pow(i, 1./3.);
	double	k = acos(-g /(2. * i));
	return(2* j * cos(k / 3) - b / ( 3 *a));
}

double			quad3_solve(double a, double b, double c, double d)
{
	double	f = (3. * c / a - pow(b, 2.) / pow(a, 2.)) / 3;
	double	g = (2. * pow(b, 3.) / pow(a, 3.) - 9. * b * c / pow(a, 2.) + 27 * d / a) / 27;
	double	h = pow(g, 2) / 4 + pow(f, 3.) / 27;
	if ( h > 0)
		return (case1(g, h, a, b));
	else
	{
		return (case2(g, h, a, b));
	}
}
int		quad4_solve(double a, double b, double c, double d, t_interval *interval)
{
	double y = quad3_solve(1, -b,a * c - 4 *d,-pow(a,2) * d - pow(c,2) + 4 * b * d);
	double	eps = 0;
	double	r_g[2];
	double	r_h[2];
	while (!(quad2_solve(-a, b - y - eps, r_g)))
	{
		//printf("not g\n");
		//r_g[0] = 0;
		//r_g[1] = 0;
		eps += b - y;
	}
	eps = 0;
	while (!(quad2_solve(-y, d - eps, r_h)))
	{
		//r_h[0] = 0;
		//r_h[1] = 0;
		eps += d;
		//printf("not h\n");
	}
	if (fabs(r_g[0] * r_h[1] + r_g[1] * r_h[0] - c) > fabs(r_g[0] * r_h[0] + r_g[1] * r_h[1] - c))	
		{
			double	tmp = r_h[0];
			r_h[0] = r_h[1];
			r_h[1] = tmp;
		}
	//printf("g equation: %fx2 + %fx +%f\n",1., -a, b-y);
	//printf("h equation: %fx2 + %fx +%f\n",1., -y, d);
	//printf("g1 %f g2 %f h1 %f h2 %f\n", r_g[0], r_g[1], r_h[0], r_h[1]);
	//printf("result equation: x4 +%fx3 +  %fx2 + %fx +%f\n", r_g[0] + r_g[1], r_g[0] * r_g[1] + r_h[0] + r_h[1], r_g[0] * r_h[1] + r_g[1] *r_h[0], r_h[0] *r_h[1]);
	double	root_1[2];
	double	root_2[2];
	bzero(root_1, sizeof(double) * 2);
	bzero(root_2, sizeof(double) * 2);
	if (!(quad2_solve(r_g[0], r_h[0], root_1)))
;
		//printf("not 1\n");
	if (!(quad2_solve(r_g[1], r_h[1], root_2)))
;
		//printf("not 2\n");
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
	interval->min[0].dist = root;
	interval->max[0].dist = root;
	if (root > 0)
	{
		interval->min[0].normal = OUTWARDS;
		interval->max[0].normal = INWARDS;
	}
	else
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
	}
	return (1);
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
	interval->min[0].dist = root;
	interval->max[0].dist = root;
	if (root > 0)
	{
		interval->min[0].normal = OUTWARDS;
		interval->max[0].normal = INWARDS;
	}
	else
	{
		interval->min[0].normal = INWARDS;
		interval->max[0].normal = OUTWARDS;
	}
	return (1);
}
*/
