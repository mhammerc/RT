/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <racousin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:30:22 by racousin          #+#    #+#             */
/*   Updated: 2017/04/24 15:35:56 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "renderer.h"
#include "shared.h"

t_vec3	tex_spherical_damier(t_ray ray)
{
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_get_normalized(vec3_sub(ray.collided->pos, ray.pos));
	u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	u = fmod(u, 0.10);
	v = 0.5 - asin(d.y) / M_PI;
	v = fmod(v, 0.10);
	if (u < 0.05 && v < 0.05)
		return (BLACK);
	if (u > 0.05 && v < 0.05)
		return (WHITE);
	if (u > 0.05 && v > 0.05)
		return (BLACK);
	if (u < 0.05 && v > 0.05)
		return (WHITE);
	return (WHITE);
}

t_vec3	tex_spherical(t_ray ray)
{
	t_vec3	r;
	t_vec3	d;
	double	u;
	double	v;
	int		offset;

	d = vec3_get_normalized(vec3_sub(ray.collided->pos, ray.pos));
	u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	u *= ray.collided->texture.width;
	v = 0.5 - asin(d.y) / M_PI;
	v *= ray.collided->texture.height;
	offset = 3;
	if (ray.collided->texture.has_alpha)
		offset = 4;
	r.x = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride];
	r.y = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride + 1];
	r.z = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride + 2];
	r = vec3_mult(1. / 256., r);
	return (r);
}

t_vec3	tex_spherical_perlin(t_ray ray)
{
	t_vec3	r;
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_get_normalized(vec3_sub(ray.collided->pos, ray.pos));
	u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	v = 0.5 - asin(d.y) / M_PI;
	r.x = ft_perlin(u * 40, v * 40, 100);
	r.y = ft_perlin(u * 40, v * 40, 100);
	r.z = ft_perlin(u * 40, v * 40, 100);
	r = vec3_mult(1. / 256., r);
	r = vec3_mult(100, r);
	return (r);
}
