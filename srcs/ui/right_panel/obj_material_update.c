/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_material_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:29:50 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/23 00:26:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	rindex_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->rindex = value;
	element_edited();
}

static void	transmittance_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->transmittance = value;
	element_edited();
}

static void	reflectance_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->reflectance = value;
	element_edited();
}

void		add_material_widgets(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	GtkWidget	*rindex;
	GtkWidget	*transmittance;
	GtkWidget	*reflectance;

	rindex = create_scale_entry("rindex", focused_obj->rindex, 1, 2);
	g_signal_connect(rindex, "rt-scale-entry-edited",
			G_CALLBACK(rindex_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), rindex);
	transmittance = create_scale_entry("transmittance",
											focused_obj->transmittance, 0, 1);
	g_signal_connect(transmittance, "rt-scale-entry-edited",
			G_CALLBACK(transmittance_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), transmittance);
	reflectance = create_scale_entry("reflectance",
											focused_obj->reflectance, 0, 1);
	g_signal_connect(reflectance, "rt-scale-entry-edited",
			G_CALLBACK(reflectance_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), reflectance);
}
