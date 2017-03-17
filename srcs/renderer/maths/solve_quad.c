/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:09:33 by racousin          #+#    #+#             */
/*   Updated: 2017/03/17 16:29:21 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "renderer.h"

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
		printf("4 root\n");



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
		printf("Q negatif\n");
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
