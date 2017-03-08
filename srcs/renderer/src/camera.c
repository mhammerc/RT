/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 20:16:28 by vfour             #+#    #+#             */
/*   Updated: 2017/03/01 16:50:22 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "rtv1.h"

static t_cam	*camera_param(t_cam *cam, int w, int h)
{
	t_vec3		lookat;
	t_f			screen_dist;

	(void)h;
	screen_dist = 0.5 * (t_f)w / tan(0.5 * cam->fov * DEG_TO_RAD);
	lookat = vec3_get_normalized(vec3_sub(cam->aim, cam->pos));
	cam->aim = vec3_add(cam->pos, vec3_mult(screen_dist, lookat));
	cam->vx = vec3_get_normalized(vec3_cross(lookat, cam->up));
	cam->vy = vec3_get_normalized(vec3_cross(cam->vx, lookat));
	cam->vx = vec3_get_normalized(vec3_cross(lookat, cam->vy));
	cam->vy = vec3_mult(cam->ratio, cam->vy);
	cam->top_left = vec3_add(cam->pos, vec3_mult(screen_dist, lookat));
	cam->top_left = vec3_add(cam->top_left, vec3_mult(0.5 * h, cam->vy));
	cam->top_left = vec3_sub(cam->top_left, vec3_mult(0.5 * w, cam->vx));
	printf("top_left:%f, %f, %f\n", cam->top_left.x, cam->top_left.y, cam->top_left.z);
	printf("vx:%f, %f, %f\n", cam->vx.x, cam->vx.y, cam->vx.z);
	printf("vy:%f, %f, %f\n", cam->vy.x, cam->vy.y, cam->vy.z);
	return (cam);
}

/*
 ** Create a cam object given string from scene file
 ** @return cam object or null
 */

t_cam			*camera_new(char **t, int w, int h)
{
	t_cam		*cam;

	(void)h;
	if (NULL == (cam = (t_cam*)ft_memalloc(sizeof(t_cam))))
		ft_exit("Camera malloc failed", EXIT_FAILURE);
	cam->pos = (t_vec3){ft_atof(*t), ft_atof(*(t + 1)), ft_atof(*(t + 2))};
	cam->aim = (t_vec3){ft_atof(*(t + 3)),
		ft_atof(*(t + 4)),
		ft_atof(*(t + 5))};
	cam->up = (t_vec3){ft_atof(*(t + 6)), ft_atof(*(t + 7)), ft_atof(*(t + 8))};
	cam->fov = ft_atof(*(t + 9));
	cam->ratio = ft_atof(*(t + 10));
	return (camera_param(cam, w, h));
}

void			camera_look(t_cam *cam, t_vec3 new_aim, int w, int h)
{
	cam->aim = new_aim;
	cam = camera_param(cam, w, h);
}

void			camera_move(t_cam *cam, t_vec3 new_pos, int w, int h)
{
	cam->pos = new_pos;
	cam = camera_param(cam, w, h);
}
