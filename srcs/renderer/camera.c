/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:44:23 by vfour             #+#    #+#             */
/*   Updated: 2017/03/04 17:10:58 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "renderer.h"
#include "shared.h"

t_cam			camera_set(t_cam cam)
{
	t_vec3		lookat;
	double		screen_dist;

	screen_dist = 0.5 * (double)cam.w / (double)tan(0.5 * cam.fov * DEG_TO_RAD);
	lookat = vec3_get_normalized(vec3_sub(cam.dir, cam.pos));
	cam.dir = vec3_add(cam.pos, vec3_mult(screen_dist, lookat));
	cam.vx = vec3_get_normalized(vec3_cross(lookat, cam.up));
	cam.vy = vec3_get_normalized(vec3_cross(cam.vx, lookat));
	cam.vx = vec3_get_normalized(vec3_cross(lookat, cam.vy));
	cam.vy = vec3_mult(cam.ratio, cam.vy);
	cam.top_left = vec3_add(cam.pos, vec3_mult(screen_dist, lookat));
	cam.top_left = vec3_add(cam.top_left, vec3_mult(0.5 * cam.h, cam.vy));
	cam.top_left = vec3_sub(cam.top_left, vec3_mult(0.5 * cam.w, cam.vx));
	return (cam);
}
