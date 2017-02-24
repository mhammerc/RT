#include <env.h>
/*
int		compute_shaded_color(t_app *app, int color, double shade)
{
	int		shaded_color;
	double	l;

	l = app->config.ambiant_light;
	shaded_color = (int)((double)(color & 0x0000FF)
						 			* (l + (1 - l) * shade)) & 0x0000FF;
	shaded_color += (int)((double)(color & 0x00FF00)
						  			* (l + (1 - l) * shade)) & 0x00FF00;
	shaded_color += (int)((double)(color & 0xFF0000)
						  			* (l + (1 - l) * shade)) & 0xFF0000;
	return (shaded_color);
}
*/
int	ft_solve(float a, float b, float c, float *t)
{
	float	delta;
	float	q;
	float	t0;
	float	t1;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	q = (b > 0) ? -0.5 * (b +sqrt(delta)) : -0.5 * (b - sqrt(delta));
	//q = -0.5 * (b +sqrt(delta));
	t0 = q / a;
	t1 = c / q;
	if (t0 > t1)
		*t = t1;
	else
		*t = t0;
	if(*t < 0)
		return (0);
	return (1);
}

__kernel void compute_color(__global int* pixels)
{
	int		pos;

//ce qu il faudra passer en parametre
	t_scene	scene;
	scene.s_x = 800;
	scene.s_y = 600;
	scene.nb_ray = 800 * 600;		

	t_cam	cam;
	cam.origine.xyz=0;

	t_obj	sphere;
	sphere.origine.xy=0;
	sphere.origine.z=-20;
	sphere.size=4;
	sphere.col=150;

	t_spot spot;
	spot.origine.xyz=0;


    pos = get_global_id(0);


//init ray
	t_ray	ray;
	int	i;
	int	j;

	i = pos % scene.s_x;
	j = pos / scene.s_x;
	ray.dir.x = ((2. * (i + 0.5) / scene.s_x) - 1.) * 0.414 * scene.s_x / scene.s_y;
	ray.dir.y = (1. - 2. * (j + 0.5) / scene.s_y) * 0.414;
	ray.dir.z = -1;
	ray.origine = cam.origine;
	ray.t = 100000; //TODO max vue



//test intersectio
	float		t;
	float3		o_c;

		t = 0.;
		o_c = ray.origine - sphere.origine;
		if(ft_solve(dot(ray.dir, ray.dir), 2 * dot((ray).dir, o_c), dot(o_c, o_c) - sphere.size * sphere.size, &t))
		{
			if (t < ray.t)
				{
					ray.t = t;
					ray.hit = ray.origine +  t * ray.dir;


//determine couleur
					int	cache;
					float3	normal;
					float3	L;
					float3	H;

					normal = ray.hit -  sphere.origine;
					normal = normal / length(normal);
					L = spot.origine -  ray.hit;
					L = L / length(L);
					H = 0.72f * ( L - (ray.dir / length(ray.dir)));
					cache = 1;
					pixels[pos] = 0xff000000 + ((int)(150.f * cache * dot(normal, L) + dot(normal, H)) & 0xff); 
				}
				else
					pixels[pos] = 0xffff0000; 
		}
}
