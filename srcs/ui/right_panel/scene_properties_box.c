/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_properties_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:33:35 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/24 15:48:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	create_ambient_light(t_ui *ui)
{
	GtkWidget	*ambiant_light;

	ambiant_light = create_scale_entry("Ambiant Light	",
		ui->rp->scene_gtk.ambiant_light, 0, 1);
	g_signal_connect(ambiant_light, "rt-scale-entry-edited",
		G_CALLBACK(ambiant_light_edited), ui);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), ambiant_light);
}

void	create_fov_box(t_ui *ui)
{
	GtkWidget	*fov;

	fov = create_scale_entry("FOV      	        ",
		ui->rp->scene_gtk.fov, 45, 90);
	g_signal_connect(fov, "rt-scale-entry-edited", G_CALLBACK(fov_edited), ui);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), fov);
}

void	create_filters_box(t_ui *ui)
{
	GtkWidget	*filters_box;
	GtkWidget	*filters_title;
	GtkWidget	*filters;

	filters_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	filters_title = gtk_label_new_with_mnemonic("Filters		");
	filters = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "Cartoon");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "Black & White");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "Sepia");
	gtk_combo_box_set_active(GTK_COMBO_BOX(filters), 0);
	g_signal_connect(filters, "changed", G_CALLBACK(filters_edited), ui);
	gtk_widget_set_size_request(filters, 158, 0);
	gtk_container_add(GTK_CONTAINER(filters_box), filters_title);
	gtk_container_add(GTK_CONTAINER(filters_box), filters);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), filters_box);
}

void	create_aa_box(t_ui *ui)
{
	GtkWidget	*aa_box;
	GtkWidget	*aa_title;
	GtkWidget	*aa;

	aa_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	aa_title = gtk_label_new_with_mnemonic("Antialiasing	");
	aa = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "2x2");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "4x4");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "8x8");
	gtk_combo_box_set_active(GTK_COMBO_BOX(aa), 0);
	g_signal_connect(aa, "changed", G_CALLBACK(aa_edited), ui);
	gtk_widget_set_size_request(aa, 158, 0);
	gtk_container_add(GTK_CONTAINER(aa_box), aa_title);
	gtk_container_add(GTK_CONTAINER(aa_box), aa);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), aa_box);
}
