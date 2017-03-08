/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 22:28:37 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:04:00 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "rtv1.h"

void		look(t_env *e, t_f varx, t_f vary)
{
	t_vec3	new_aim;
	t_vec3	vx;
	t_vec3	vy;

	new_aim = e->sce->cam->aim;
	vx = e->sce->cam->vx;
	vy = e->sce->cam->vy;
	vx = vec3_mult(varx, vx);
	vy = vec3_mult(vary, vy);
	new_aim = vec3_add(new_aim, vx);
	new_aim = vec3_add(new_aim, vy);
	camera_look(e->sce->cam, new_aim, e->w, e->h);
}

void		move(t_env *e, t_f varfront, t_f varright, t_f varup)
{
	t_vec3	new_pos;
	t_vec3	vright;
	t_vec3	vfront;
	t_vec3	vup;

	new_pos = e->sce->cam->pos;
	vfront = vec3_sub(e->sce->cam->aim, e->sce->cam->pos);
	vfront = vec3_mult(varfront, vec3_get_normalized(vfront));
	vright = vec3_mult(varright, e->sce->cam->vx);
	vup = vec3_mult(varup, e->sce->cam->vy);
	new_pos = vec3_add(new_pos, vfront);
	new_pos = vec3_add(new_pos, vright);
	new_pos = vec3_add(new_pos, vup);
	camera_move(e->sce->cam, new_pos, e->w, e->h);
}

int			mouse_motion(int x, int y, t_env *e)
{
	int		varx;
	int		vary;

	if (e->mouse_x == INT_MIN)
	{
		e->mouse_x = x;
		e->mouse_y = y;
		return (0);
	}
	varx = x - e->mouse_x;
	vary = e->mouse_y - y;
	e->mouse_x = x;
	e->mouse_y = y;
	look(e, (t_f)varx, (t_f)vary);
	draw(e);
	return (0);
}
