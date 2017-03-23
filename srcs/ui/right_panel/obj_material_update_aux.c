/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_material_update_aux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 00:24:19 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/23 11:31:08 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	kdiff_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kdiff = value;
	element_edited();
}

static void	kspec_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kspec = value;
	element_edited();
}

void		add_material_widgets_aux(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	GtkWidget	*kdiff;
	GtkWidget	*kspec;

	kdiff = create_scale_entry("Kdiff	", focused_obj->kdiff, 0, 1);
	g_signal_connect(kdiff, "rt-scale-entry-edited", G_CALLBACK(kdiff_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), kdiff);
	kspec = create_scale_entry("Kspec	", focused_obj->kspec, 0, 1);
	g_signal_connect(kspec, "rt-scale-entry-edited", G_CALLBACK(kspec_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), kspec);
}
