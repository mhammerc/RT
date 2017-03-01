/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:44:23 by vfour             #+#    #+#             */
/*   Updated: 2017/03/01 16:50:08 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "env.h"

t_cam			camera_set(t_cam cam)
{
	FLOAT3		lookat;
	FLOAT		screen_dist;

	screen_dist = 0.5 * (FLOAT)cam.w / (FLOAT)tan(0.5 * cam.fov * DEG_TO_RAD);
	lookat = vec3_get_normalized(vec3_sub(cam.dir, cam.pos));
	cam.dir = vec3_add(cam.pos, vec3_mult(screen_dist, lookat));
	cam.vx = vec3_get_normalized(vec3_cross(lookat, cam.up));
	cam.vy = vec3_get_normalized(vec3_cross(cam.vx, lookat));
	cam.vx = vec3_get_normalized(vec3_cross(lookat, cam.vy));
	cam.vy = vec3_mult(cam.ratio, cam.vy);
	cam.top_left = vec3_add(cam.pos, vec3_mult(screen_dist, lookat));
	cam.top_left = vec3_add(cam.top_left, vec3_mult(0.5 * cam.h, cam.vy));
	cam.top_left = vec3_sub(cam.top_left, vec3_mult(0.5 * cam.w, cam.vx));
	printf("top_left:%f, %f, %f\n", cam.top_left.x, cam.top_left.y, cam.top_left.z);
	printf("vx:%f, %f, %f\n", cam.vx.x, cam.vx.y, cam.vx.z);
	printf("vy:%f, %f, %f\n", cam.vy.x, cam.vy.y, cam.vy.z);
	return (cam);
}
