/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 22:28:31 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:04:07 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

static int	expose_hook(void *p)
{
	t_env	*e;

	e = (t_env*)p;
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	return (0);
}

static int	red_cross(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

static int	key_press(int key, t_env *e)
{
	if (key == KEY_RIGHT)
		look(e, 10, 0);
	if (key == KEY_LEFT)
		look(e, -10, 0);
	if (key == KEY_UP)
		look(e, 0, 10);
	if (key == KEY_DOWN)
		look(e, 0, -10);
	if (key == KEY_W)
		move(e, 0.1, 0, 0);
	if (key == KEY_S)
		move(e, -0.1, 0, 0);
	if (key == KEY_A)
		move(e, 0, -0.1, 0);
	if (key == KEY_D)
		move(e, 0, 0.1, 0);
	if (key == KEY_R)
		move(e, 0, 0, 0.1);
	if (key == KEY_F)
		move(e, 0, 0, -0.1);
	draw(e);
	return (0);
}

static int	key_release(int key, t_env *e)
{
	(void)e;
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

void		init_hooks(t_env *e)
{
	mlx_hook(e->win_ptr, 17, (1L << 17), &red_cross, e);
	mlx_hook(e->win_ptr, MOTIONNOTIFY, POINTERMOTIONMASK, &mouse_motion, e);
	mlx_hook(e->win_ptr, KEYPRESS, KEYPRESSMASK, &key_press, e);
	mlx_hook(e->win_ptr, KEYRELEASE, KEYRELEASEMASK, &key_release, e);
	mlx_expose_hook(e->win_ptr, &expose_hook, e);
}
