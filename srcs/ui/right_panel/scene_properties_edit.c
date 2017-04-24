/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_properties_edit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:33:21 by aditsch           #+#    #+#             */
/*   Updated: 2017/04/24 15:27:59 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		aa_edited(GtkComboBox *widget, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.aa = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	scene_edited();
}

void		filters_edited(GtkComboBox *widget, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.filter = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	scene_edited();
}

void		ambiant_light_edited(GtkWidget *widget, gdouble value,
					gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->rp->scene_gtk.ambiant_light = value;
	scene_edited();
}

void		fov_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->rp->scene_gtk.fov = value;
	scene_edited();
}
