/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:35:51 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/22 21:39:02 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "converter.h"

static void		pos_edited(GtkWidget *widget, t_vec3 *pos, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->pos = *pos;
	free(pos);
	cam_edited();
}

void			edit_cam_properties(gpointer data)
{
	t_ui		*view;

	view = (t_ui*)data;
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop),
		gtk_label_new_with_mnemonic("_Camera"));
	view->rp->pos = create_vector3_entry("pos		", view->cam->pos);
	view->rp->lkat = create_vector3_entry("LookAt	", view->cam->dir);
	view->rp->up = create_vector3_entry("Up           ", view->cam->up);
	g_signal_connect(view->rp->pos, "rt-vector3-entry-edited",
		G_CALLBACK(pos_edited), view);
	g_signal_connect(view->rp->lkat, "rt-vector3-entry-edited",
		G_CALLBACK(dir_edited), view);
	g_signal_connect(view->rp->up, "rt-vector3-entry-edited",
		G_CALLBACK(up_edited), view);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->pos);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->lkat);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->up);
	gtk_widget_show_all(view->window);
}

static void		add_to_container(t_ui *ui)
{
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->pos);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->lkat);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->up);
}

void			refresh_cam_properties(t_ui *ui)
{
	GList		*children;
	GList		*iter;

	children = gtk_container_get_children(GTK_CONTAINER(ui->rp->cam_prop));
	iter = children;
	while (iter)
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));
		iter = g_list_next(iter);
	}
	g_list_free(children);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop),
		gtk_label_new_with_mnemonic("_Camera"));
	ui->rp->pos = create_vector3_entry("pos		", ui->cam->pos);
	ui->rp->lkat = create_vector3_entry("LookAt	", ui->cam->dir);
	ui->rp->up = create_vector3_entry("Up           ", ui->cam->up);
	g_signal_connect(ui->rp->pos, "rt-vector3-entry-edited",
		G_CALLBACK(pos_edited), ui);
	g_signal_connect(ui->rp->lkat, "rt-vector3-entry-edited",
		G_CALLBACK(dir_edited), ui);
	g_signal_connect(ui->rp->up, "rt-vector3-entry-edited",
		G_CALLBACK(up_edited), ui);
	add_to_container(ui);
	gtk_widget_show_all(ui->rp->cam_prop);
}
