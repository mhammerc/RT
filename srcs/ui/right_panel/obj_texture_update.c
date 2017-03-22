/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:30:24 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 22:31:54 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void		texture_type_upd(GtkComboBox *widget, gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	(void)widget;
	ui->selected_obj.object->have_texture =
								gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	element_edited();
}

static void		texture_file_set(GtkFileChooserButton *widget, gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	if (ui->rendering)
		return ;
	free_texture(&ui->selected_obj.object->texture);
	if (ui->selected_obj.object->texture_filename)
		g_free(ui->selected_obj.object->texture_filename);
	ui->selected_obj.object->texture_filename =
						gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
	ui->selected_obj.object->texture =
						load_texture(ui->selected_obj.object->texture_filename);
	if (!ui->selected_obj.object->texture.is_valid)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window),
						GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
						"Can not load %s.\nIt is not a valid texture.\n%s",
						ui->selected_obj.object->filename, g_strerror(errno));
		g_signal_connect_swapped(dialog, "response",
										G_CALLBACK(gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		return ;
	}
	element_edited();
}

void	add_texture_widgets(t_ui *ui, t_object *focused_obj, GtkWidget *props)
{
	GtkWidget	*texture_type_box;
	GtkWidget	*texture_type_title;
	GtkWidget	*texture_type;

	GtkWidget	*texture_box;
	GtkWidget	*texture_title;
	GtkWidget	*texture_chooser;

	texture_type_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	texture_type_title = gtk_label_new_with_mnemonic("Texture type	");
	texture_type = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Spherical");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Sphere damier");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Planar");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Planar damier");
	gtk_combo_box_set_active(GTK_COMBO_BOX(texture_type), focused_obj->have_texture);
	g_signal_connect(texture_type, "changed", G_CALLBACK(texture_type_upd), ui);
	gtk_widget_set_size_request(texture_type, 130, 0);
	gtk_container_add(GTK_CONTAINER(texture_type_box), texture_type_title);
	gtk_container_add(GTK_CONTAINER(texture_type_box), texture_type);
	gtk_container_add(GTK_CONTAINER(props), texture_type_box);

	texture_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	texture_title = gtk_label_new_with_mnemonic("Texture		");
	texture_chooser = gtk_file_chooser_button_new("Texture images", GTK_FILE_CHOOSER_ACTION_OPEN);
	if (focused_obj->texture_filename)
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(texture_chooser), focused_obj->texture_filename);
	g_signal_connect(texture_chooser, "file-set", G_CALLBACK(texture_file_set), ui);
	gtk_widget_set_size_request(texture_chooser, 130, 0);
	gtk_container_add(GTK_CONTAINER(texture_box), texture_title);
	gtk_container_add(GTK_CONTAINER(texture_box), texture_chooser);
	gtk_container_add(GTK_CONTAINER(props), texture_box);
}
