/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <vfour@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:29:01 by vfour             #+#    #+#             */
/*   Updated: 2017/03/24 15:31:09 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

int			colorcomp_to_rgb(t_scene *sce, int r, int g, int b)
{
	r = r < 0 ? 0 : (r & 0xff);
	g = g < 0 ? 0 : (g & 0xff);
	b = b < 0 ? 0 : (b & 0xff);
	if (sce->filter == CARTOON)
		filter_cartoon(&r, &g, &b);
	return ((0xff << ALPHA_BITSHIFT)
			+ (r << R_BITSHIFT)
			+ (g << G_BITSHIFT)
			+ (b << B_BITSHIFT));
}

/*
** Exposure function: color = 255 * (1 - exp(constant * light));
*/

void		light_to_pixel(t_scene *sce, t_vec3 *light, int *px)
{
	int		i;
	int		len;

	len = sce->cam.w * sce->cam.h;
	i = -1;
	if (sce->filter == BLACK_WHITE)
		filter_black_and_white(light, len);
	if (sce->filter == SEPIA)
		filter_sepia(light, len);
	while (++i < len)
	{
		px[i] = colorcomp_to_rgb(sce, 255. * (1.0 - exp(EXPOSURE * light[i].x)),
									255. * (1.0 - exp(EXPOSURE * light[i].y)),
									255. * (1.0 - exp(EXPOSURE * light[i].z)));
	}
}

/*
** Mix light with object color and coefficient
*/

t_vec3		color_light_mix(t_vec3 obj_color, t_vec3 light_color, double coeff)
{
	t_vec3	res;

	res.x = obj_color.x * light_color.x * coeff;
	res.y = obj_color.y * light_color.y * coeff;
	res.z = obj_color.z * light_color.z * coeff;
	return (res);
}

/*
** Add light contribution to a pixel
*/

t_vec3		color_add_light(t_ray ray,
							t_spot *l,
							t_vec3 obj_cam,
							t_vec3 absorbance)
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
		diff *= ray.collided->kdiff * l->intensity;
		diff *= atten * (1.0 - obj->transmittance);
		light = color_light_mix(get_texture_color(ray),
								vec3_mul(l->color, absorbance), diff);
	}
	h = vec3_get_normalized(vec3_add(obj_cam, ray.dir));
	if ((diff = fmax(pow(vec3_dot(ray.n, h), ray.collided->kp), 0)) > 0)
	{
		diff *= ray.collided->kspec * l->intensity;
		diff *= atten * (1.0 - obj->transmittance);
		light = vec3_add(light, color_light_mix(get_texture_color(ray),
								vec3_mul(l->color, absorbance), diff));
	}
	return (light);
}

/*
** Average convolution kernel
*/

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
