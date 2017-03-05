#include <raytracer.h>

//TODO: Why norm ?
int		norm_quad_solve(float b, float c, float *t)
{
	float		d;
	float		x1;
	float		x2;
	int			res;

	d = b * b - c;
	if (d < 0.)
		return (0);
	res = 0;
	d = sqrt(d);
	x1 = -b - d;
	x2 = -b + d;
	if (x1 > 0. && x1 < *t)
	{
		res = 1;
		*t = x1;
	}
	if (x2 > 0. && x2 < *t)
	{
		res = 1;
		*t = x2;
	}
	return (res);
}
