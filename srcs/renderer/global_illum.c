#include <stdlib.h>
#include "renderer.h"

static int		light_intersect(t_spot spot, t_ray ray)
{
	double		b;
	double		c;
	t_vec3		ray_sphere;
	t_interval	interval;

	if (spot.radius < EPS)
		return (0);
	ray_sphere = vec3_sub(ray.pos, spot.pos);
	b = vec3_dot(ray_sphere, ray.dir);
	c = vec3_norm2(ray_sphere) - spot.radius;
	if ((interval.nb_hit = norm_quad_solve(b, c, &interval)))
		return (1);
	return (0);
}

static t_vec3	rand_half_sphere(t_vec3 c, double r, t_vec3 n, unsigned int *seed)
{
	t_vec3	v;
	t_vec3	rand_dir;

	v = rand_sphere(c, r, seed);
	rand_dir = vec3_sub(v, c);
	while (vec3_dot(rand_dir, n) < EPS)
	{
		v = rand_sphere(c, r, seed);
		rand_dir = vec3_sub(v, c);
	}
	return (v);
}

t_vec3	global_illum(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		dir;
	t_vec3		light;
	t_vec3		new_light;
	int			i;

	i = NRAY_GLOBAL;
	new_light = (t_vec3){0, 0, 0};
	light = new_light;
	depth = depth == MAX_REC_DEPTH - 1? MAX_REC_DEPTH : MAX_REC_DEPTH - 1;
	while (--i)
	{
		dir = rand_half_sphere(ray.pos, 1, ray.n, ray.seed);
		ray.type = REFLECTION_RAY;
		new_light = ray_trace(sce, ray_new_dir(ray, vec3_get_normalized(dir)), depth);
		light = vec3_add(light, new_light);
	}
	return (color_light_mix(get_texture_color(ray), light, GLOBAL_ATTEN ));
	//return (color_light_mix(get_texture_color(ray), light, GLOBAL_ATTEN / (double)NRAY_GLOBAL));
	//return (vec3_mult(GLOBAL_ATTEN / (double)NRAY_GLOBAL, light));
}
