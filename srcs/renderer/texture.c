/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:30:08 by racousin          #+#    #+#             */
/*   Updated: 2017/04/24 13:14:57 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "renderer.h"
#include "shared.h"

static t_vec3	tex_planar2(t_ray ray, double u, double v)
{
	t_vec3	r;
	int		offset;

	u = fmod(u, 1.0) * ray.collided->texture.width;
	v = fmod(v, 1.0) * ray.collided->texture.height;
	offset = 3.;
	if (ray.collided->texture.has_alpha)
		offset = 4.;
	r.x = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride];
	r.y = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride + 1];
	r.z = ray.collided->texture.pixels[(int)u * offset
		+ (int)v * ray.collided->texture.rowstride + 2];
	r = vec3_mult(1. / 256., r);
	return (r);
}

static t_vec3	tex_planar(t_ray ray)
{
	t_vec3	tmp;
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_sub(ray.collided->pos, ray.pos);
	tmp = vec3_cross(d, ray.collided->dir);
	if (fabs(ray.collided->dir.x) < fabs(ray.collided->dir.y))
	{
		u = d.x;
		v = tmp.x;
	}
	else
	{
		u = d.y;
		v = tmp.y;
	}
	if (u < 0.)
		u = -u;
	if (v < 0.)
		v = -v;
	return (tex_planar2(ray, u, v));
}

static t_vec3	tex_planar_damier2(double u, double v)
{
	if (u < 0.)
	{
		u -= 0.5;
		u = -u;
	}
	if (v < 0.)
	{
		v -= 0.5;
		v = -v;
	}
	u = fmod(u, 1.0);
	v = fmod(v, 1.0);
	if (u < 0.5 && v < 0.5)
		return (BLACK);
	if (u > 0.5 && v < 0.5)
		return (WHITE);
	if (u > 0.5 && v > 0.5)
		return (BLACK);
	if (u < 0.5 && v > 0.5)
		return (WHITE);
	return (WHITE);
}

static t_vec3	tex_planar_damier(t_ray ray)
{
	t_vec3	tmp;
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_sub(ray.collided->pos, ray.pos);
	tmp = vec3_cross(d, ray.collided->dir);
	if (fabs(ray.collided->dir.x) < fabs(ray.collided->dir.y))
	{
		u = d.x;
		v = tmp.x;
	}
	else
	{
		u = d.y;
		v = tmp.y;
	}
	return (tex_planar_damier2(u, v));
}

t_vec3			get_texture_color(t_ray ray)
{
	if (ray.collided->have_texture == NO_TEXTURE)
		return (ray.collided->color);
	else if (ray.collided->have_texture == SPHERICAL_DAMIER)
		return (tex_spherical_damier(ray));
	else if (ray.collided->have_texture == SPHERICAL
			&& ray.collided->texture.is_valid)
		return (tex_spherical(ray));
	else if (ray.collided->have_texture == PLANAR
			&& ray.collided->texture.is_valid)
		return (tex_planar(ray));
	else if (ray.collided->have_texture == PLANAR_DAMIER)
		return (tex_planar_damier(ray));
	else if (ray.collided->have_texture == SPHERICAL_PERLIN)
		return (tex_spherical_perlin(ray));
	else
		return (ray.collided->color);
}
