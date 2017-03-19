#include <math.h>
#include "renderer.h"

/*
** Ray constructor
** @return a new ray
*/

t_ray		ray_new(t_vec3 pos, t_vec3 aim)
{
	t_vec3	n;
	t_vec3	dir;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, BIG_DIST + 1,
			INITIAL_RAY, NULL, n, n, stack_new(), LOCATION_NONE});
}

/*
** From a previous ray, creates a new ray ready for tracing with new direction
*/
t_ray		ray_new_dir(t_ray ray, t_vec3 dir)
{
	t_vec3	n;

	n = (t_vec3){0, 0, 0};
	ray.dir = dir;
	ray.t = BIG_DIST + 1;
	ray.n = n;
	ray.type = INITIAL_RAY;
	ray.collided = NULL;
	ray.location = LOCATION_NONE;
	return (ray);
}

t_ray		reflected_ray(t_ray ray)
{
	t_vec3	refl;

	refl = vec3_mult(-1, ray.dir);
	refl = vec3_add(ray.pos, vec3_mult(2 * vec3_dot(ray.n, refl), ray.n));
	refl = vec3_add(refl, ray.dir);
	refl = vec3_sub(refl, ray.pos);
	ray = ray_new_dir(ray, vec3_get_normalized(refl));
	return (ray);
}


//if collision from outside
//	- new rindex is of object collided
//	- old rindex is at top of stack
//	- if stack is empty, previous rindex is 1 (air)
//	- then stack new object
//if collision from inside
//	- pop stack and read top to get rnew, if stack is empty then rnew is 1
//	- rprev is of object collided
//compute transmitted direction
	//return refracted ray
t_ray	refracted_ray(t_ray ray)
{
	t_obj		*prev_obj;
	double		ki; //rprev : rindex incident ray
	double		kr; //rnew : rindex refracted ray
	double		n;
	double		c1;
	double		c2;
	t_vec3		Rr;
	int			size_before;

	size_before = ray.rstack.size;
	if (ray.location == LOCATION_OUTSIDE)
	{
		prev_obj = stack_peak(&(ray.rstack));
		ki = (NULL == prev_obj) ? R_DEFAULT : prev_obj->rindex;
		kr = ray.collided->rindex;
		//printf("from outside - ki:%f, kr:%f, size_before:%d\n", ki, kr, size_before);
		stack_push(&(ray.rstack), ray.collided);
	}
	else
	{
		stack_pop(&(ray.rstack));
		prev_obj = stack_peak(&(ray.rstack));
		kr = (NULL == prev_obj) ? R_DEFAULT : prev_obj->rindex;
		ki = ray.collided->rindex;
		//printf("from inside - ki:%f, kr:%f, size_before:%d\n", ki, kr, size_before);
	}
	kr = kr > 0 ? kr : R_DEFAULT;
	n = ki / kr;
	c1 = -vec3_dot(ray.dir, ray.n);
	c2 = sqrt( 1 - n * n * (1. - c1 * c1));
	Rr = vec3_add(vec3_mult(n, ray.dir),vec3_mult(n * c1 - c2, ray.n));
	ray.pos = vec3_add(ray.pos, vec3_mult(2. * EPS, ray.dir));
	return (ray_new_dir(ray, vec3_get_normalized(Rr)));
}
