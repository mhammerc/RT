#include <math.h>
#include "renderer.h"

int				colorcomp_to_rgb(int r, int g, int b)
{
	r = r < 0 ? 0 : (r & 0xff);
	g = g < 0 ? 0 : (g & 0xff);
	b = b < 0 ? 0 : (b & 0xff);
	return ((0xff << ALPHA_BITSHIFT) + (r << R_BITSHIFT) + (g << G_BITSHIFT) + (b << B_BITSHIFT));
}

void			light_to_pixel(t_vec3 *light, int *px, int w, int h)
//void			light_to_pixel(t_renderer_thread *data)
{
	double		invmax;
	double		max;
	int			i;
	int			len;

	len = w * h;
	max = 0.;
	i = -1;
	while (++i < len)
	{
		max = fmax(max, light[i].x);
		max = fmax(max, light[i].y);
		max = fmax(max, light[i].z);
	}
	invmax = 255. / max;
	i = -1;
	while (++i < len)
	{
		px[i] = colorcomp_to_rgb(light[i].x * invmax,
									light[i].y * invmax,
									light[i].z * invmax);
	}
}

/*
** Add color components
*/
t_vec3		color_light_mix(t_vec3 obj_color, t_vec3 light_color, double coeff)
{
	t_vec3	res;

	res.x = obj_color.x * light_color.x * coeff;
	res.y = obj_color.y * light_color.y * coeff;
	res.z = obj_color.z * light_color.z * coeff;
	return (res);
}

t_vec3		color_add_light(t_ray ray, t_spot *l, t_vec3 obj_cam, t_vec3 absorbance)
{
	t_vec3	light;
	double	diff;
	t_vec3	h;
	double	atten;
	t_obj	*obj;

	atten = 1.0 / (ray.t);
	light = (t_vec3){0, 0, 0};
	obj = ray.collided;
	if ((diff = fmax(vec3_dot(ray.dir, ray.n), 0)) > 0)
	{
		diff *= ray.collided->kdiff * l->intensity * atten * (1.0 - obj->transmittance);
		light = color_light_mix(obj->color, vec3_mul(l->color, absorbance), diff);
	}
	h = vec3_get_normalized(vec3_add(obj_cam, ray.dir));
	if ((diff = fmax(pow(vec3_dot(ray.n, h), ray.collided->kp), 0)) > 0)
	{
		diff *= ray.collided->kspec * l->intensity * atten * (1.0 - obj->transmittance);
		light = vec3_add(light, color_light_mix(obj->color, vec3_mul(l->color, absorbance), diff));
	}
	return (light);
}

t_vec3		color_average(t_vec3 *aa, int size)
{
	t_vec3	r;
	int		i;

	r = (t_vec3){0., 0., 0.};
	i = 0;
	while (i < size)
		r = vec3_add(r, aa[i++]);
	return (vec3_mult(1. / (double)size, r));
}

