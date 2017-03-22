/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_situational_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:32:45 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/23 00:28:29 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void		radius_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->radius = value;
	element_edited();
}

static void		length_upd(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->length = value;
	element_edited();
}

static void		add_situational_widgets_aux(t_ui *ui, t_object *focused_obj,
									GtkWidget *props, enum e_object_type type)
{
	GtkWidget	*radius;
	GtkWidget	*length;

	if (type == SPHERE || type == CONE || type == CYLINDER ||
												type == TORUS || type == DISK)
	{
		radius = create_scale_entry("Radius	", focused_obj->radius, 0, 1000);
		g_signal_connect(radius, "rt-scale-entry-edited",
													G_CALLBACK(radius_upd), ui);
		gtk_container_add(GTK_CONTAINER(props), radius);
	}
	if (type == CONE || type == CYLINDER || type == TORUS || type == POLYGONS)
	{
		length = create_scale_entry("Length	", focused_obj->length, 0, 1000);
		g_signal_connect(length, "rt-scale-entry-edited",
													G_CALLBACK(length_upd), ui);
		gtk_container_add(GTK_CONTAINER(props), length);
	}
	if (type == LIGHT)
	{
		length = create_scale_entry("Intensity	", focused_obj->length, 0, 100);
		g_signal_connect(length, "rt-scale-entry-edited",
													G_CALLBACK(length_upd), ui);
		gtk_container_add(GTK_CONTAINER(props), length);
	}
}

void			add_situational_widgets(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	enum e_object_type	type;

	type = ui->selected_obj.object->type;
	add_situational_widgets_aux(ui, focused_obj, props, type);
	if (type != CSG)
		create_color_chooser(ui, focused_obj->color);
	if (type != CSG || type != EMPTY || type != LIGHT)
	{
		add_material_widgets_aux(ui, focused_obj, props);
		add_material_widgets(ui, focused_obj, props);
	}
	if (type == CSG)
		add_csg_widgets(ui, focused_obj, props);
	if (type != CSG && type != LIGHT)
	{
		add_texture_type_widgets(ui, focused_obj, props);
		add_texture_chooser_widgets(ui, focused_obj, props);
	}
	if (type == POLYGONS)
		add_objext_widgets(ui, focused_obj, props);
}
