/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_properties_edit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:34:05 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/22 21:38:19 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "converter.h"

void		init_cam(t_ui *ui)
{
	t_ui_cam	*cam;

	cam = (t_ui_cam*)monloc(sizeof(t_cam));
	if (!cam)
		exit(EXIT_FAILURE);
	ft_bzero(cam, sizeof(t_cam));
	cam->pos = (t_vec3){0., 0., 7.};
	cam->dir = (t_vec3){0., 0., 0.};
	cam->up = (t_vec3){0., 1., 0.};
	ui->cam = cam;
}

void		cam_edited(void)
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

void		dir_edited(GtkWidget *widget, t_vec3 *dir, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->dir = *dir;
	free(dir);
	cam_edited();
}

void		up_edited(GtkWidget *widget, t_vec3 *up, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->up = *up;
	free(up);
	cam_edited();
}
