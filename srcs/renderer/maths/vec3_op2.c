#include <math.h>
#include "renderer.h"
#include "shared.h"

t_vec3		vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3		vec3_apply(t_vec3 a, double (*f)(double x))
{
	return ((t_vec3){(*f)(a.x), (*f)(a.y), (*f)(a.z)});
}
