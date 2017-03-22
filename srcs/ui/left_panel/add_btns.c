/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_btns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:42:18 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 17:45:37 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	create_btn(GtkWidget *parent, char *label, void (*f)(gboolean))
{
	GtkWidget	*btn;

	btn = gtk_button_new_with_label(label);
	g_signal_connect(btn, "clicked", G_CALLBACK(f), NULL);
	gtk_container_add(GTK_CONTAINER(parent), btn);
}

void		add_obj_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget	*popover;
	GtkWidget	*submenu;

	(void)button;
	ui = (t_ui*)view;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover), ui->lp->lp_btns.add_obj);
	submenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	create_btn(submenu, "Sphere", create_sphere);
	create_btn(submenu, "Empty", create_empty);
	create_btn(submenu, "Plane", create_plane);
	create_btn(submenu, "Disk", create_disk);
	create_btn(submenu, "Cylinder", create_cylinder);
	create_btn(submenu, "Cone", create_cone);
	create_btn(submenu, "Torus", create_torus);
	create_btn(submenu, "CSG", create_cgs);
	create_btn(submenu, "Polygons", create_polygons);
	gtk_container_add(GTK_CONTAINER(popover), submenu);
	gtk_widget_show_all(popover);
}

void		add_light_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget	*popover;
	GtkWidget	*submenu;
	GtkWidget	*light;

	(void)button;
	ui = (t_ui*)view;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover),
													ui->lp->lp_btns.add_light);
	submenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	light = gtk_button_new_with_label("Diffuse");
	g_signal_connect(light, "clicked", G_CALLBACK(create_light), NULL);
	gtk_container_add(GTK_CONTAINER(submenu), light);
	gtk_container_add(GTK_CONTAINER(popover), submenu);
	gtk_widget_show_all(popover);
}
