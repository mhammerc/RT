/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_shared_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:28:58 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/23 11:43:48 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	object_name_upd(GtkWidget *emitter, gchar *new_text, gpointer data)
{
	t_object	*obj;
	t_ui		*ui;

	(void)emitter;
	(void)data;
	ui = get_interface();
	obj = ui->selected_obj.object;
	ft_strcpy(obj->name, new_text);
	gtk_tree_store_set(GTK_TREE_STORE(ui->lp->tree.store),
		&ui->selected_obj.iter, 0, obj->name, -1);
}

static void	pos_upd(GtkWidget *widget, t_vec3 *pos, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->pos = *pos;
	free(pos);
	element_edited();
}

static void	rot_upd(GtkWidget *widget, t_vec3 *rot, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->rot = *rot;
	free(rot);
	element_edited();
}

void		add_shared_widgets(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	GtkWidget	*name;
	GtkWidget	*pos;
	GtkWidget	*rot;

	name = create_text_entry("Name	", focused_obj->name);
	g_signal_connect(G_OBJECT(name), "rt-entry-edited",
									G_CALLBACK(object_name_upd), (gpointer)ui);
	gtk_container_add(GTK_CONTAINER(props), name);
	pos = create_vector3_entry("Pos		", focused_obj->pos);
	g_signal_connect(pos, "rt-vector3-entry-edited", G_CALLBACK(pos_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), pos);
	rot = create_vector3_entry("Rot		", focused_obj->rot);
	g_signal_connect(rot, "rt-vector3-entry-edited", G_CALLBACK(rot_upd), ui);
	gtk_container_add(GTK_CONTAINER(props), rot);
}
