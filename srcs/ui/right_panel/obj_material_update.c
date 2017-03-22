/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_material_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:29:50 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 22:32:06 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void		kdiff_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kdiff = value;
	element_edited();
}

static void		kspec_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kspec = value;
	element_edited();
}

static void		rindex_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->rindex = value;
	element_edited();
}

static void		transmittance_upd(GtkWidget *widget, gdouble value,
																gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->transmittance = value;
	element_edited();
}

void		add_material_widgets(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	GtkWidget	*kdiff;
	GtkWidget	*kspec;
	GtkWidget	*rindex;
	GtkWidget	*transmittance;

	kdiff = create_scale_entry("kdiff		", focused_obj->kdiff, 0, 1);
	g_signal_connect(kdiff, "rt-scale-entry-edited", G_CALLBACK(kdiff_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), kdiff);
	kspec = create_scale_entry("Kspec	", focused_obj->kspec, 0, 1);
	g_signal_connect(kspec, "rt-scale-entry-edited", G_CALLBACK(kspec_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), kspec);
	rindex = create_scale_entry("rindex", focused_obj->rindex, 1, 2);
	g_signal_connect(rindex, "rt-scale-entry-edited",
			G_CALLBACK(rindex_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), rindex);
	transmittance = create_scale_entry("transmittance",
											focused_obj->transmittance, 0, 1);
	g_signal_connect(transmittance, "rt-scale-entry-edited",
			G_CALLBACK(transmittance_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), transmittance);
}
