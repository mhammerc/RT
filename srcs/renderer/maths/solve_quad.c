/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:09:33 by racousin          #+#    #+#             */
/*   Updated: 2017/03/14 16:08:47 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
/*
int			quad4_solve(double a, double b, double c, double d, double e, t_interval *interval)
{
	double		d;
	double		x1;
	double		x2;
	double		x3;
	double		x4;

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
*/

int			quad4_solve(double a, double b, double c, double d, double e, double *root)
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
	double Q = pow( (delta1 + sqrt(delta1 * delta1 - 4. * delta0 * delta0 * delta0)) / 2., 1.0 / 3.0);
	double	S = sqrt(-2. * p /3. + (Q + delta0 / Q)/3.)/2.;
	//printf("S %f\n", S);
	nb_root = 4;
	double	tmp1 = -4. * pow (S, 2.) - 2. *p + q / S;
	//printf("tmp1 %f\n", tmp1);
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
	//printf("x1 %f, x2%f\n", x1, x2);
	double	tmp2 = -4. * pow (S, 2.) - 2. *p - q/S;
	//printf("tmp2 %f\n", tmp2);
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
	//printf("nb_root %d\n", nb_root);
	//printf("x3 %f, x4%f\n", x3, x4);
	//printf("ax1 +bx1 +x..= %f\n", a * pow(x1, 4.) +b* pow(x1,3.) + c*pow(x1,2.) + d*x1 + e);
	//printf("ax2 +bx2 +x..= %f\n", a* pow(x2, 4.) +b* pow(x2,3.) + c* pow(x2,2.) + d*x2 + e);
	//printf("ax3 +bx3 +x..= %f\n", a * pow(x3, 4.) +b* pow(x3,3.) + c*pow(x3,2.) + d*x3 + e);
	//printf("ax4 +bx4 +x..= %f\n", a* pow(x4, 4.) +b* pow(x4,3.) + c* pow(x4,2.) + d*x4 + e);
	if ( x1 > 0 && x1 < x2 && x1 < x3 && x1 < x4 )
		*root = x1;
	if ( x2 > 0 && x2 < x1 && x2 < x3 && x2 < x4 )
		*root = x2;
	if ( x3 > 0 && x3 < x1 && x3 < x2 && x3 < x4 )
		*root = x3;
	if ( x4 > 0 && x4 < x1 && x4 < x2 && x4 < x3 )
		*root = x4;
	return (nb_root);
}
