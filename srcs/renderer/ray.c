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

t_ray		reflected_ray(t_ray ray)
{
	t_vec3	refl;

	refl = vec3_mult(-1, ray.dir);
	refl = vec3_add(ray.pos, vec3_mult(2 * vec3_dot(ray.n, refl), ray.n));
	refl = vec3_add(refl, ray.dir);
	ray = ray_new(ray.pos, refl);
	return (ray);
}

/*
t_ray		ray_new_aim(t_ray ray, t_vec3 pos, t_vec3 aim)
{
	t_vec3	n;
	t_vec3	dir;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, BIG_DIST + 1,  INITIAL_RAY, NULL, n, n});
}
*/

/*
static t_ray	refracted_ray(t_ray ray)
{

	//if collision from outside, stack new rindex
	//if collision from inside, pop rindex
	//return refracted ray
	if (ray.location == LOCATION_OUTSIDE)
	{
	}
	else if (ray.location == LOCATION_INSIDE)
	{
	}
	return (r);
}
*/
