/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_obj_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:28:58 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 23:13:13 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "obj_parser.h"

static void		wavefront_file_set(GtkFileChooserButton *widget,
					gpointer user_data)
{
	t_ui		*ui;
	t_object	*object;
	GtkWidget	*dialog;
	size_t		i;

	ui = (t_ui*)user_data;
	if (ui->rendering)
		return ;
	if (ui->selected_obj.object->filename)
		g_free(ui->selected_obj.object->filename);
	if (ui->selected_obj.object->faces)
	{
		i = 0;
		while (i < ui->selected_obj.object->nb_faces)
		{
			free(ui->selected_obj.object->faces[i].sommets);
			free(ui->selected_obj.object->faces[i].normales);
			free(ui->selected_obj.object->faces[i].textures);
			++i;
		}
		free(ui->selected_obj.object->faces);
	}
	ui->selected_obj.object->filename = gtk_file_chooser_get_filename(
		GTK_FILE_CHOOSER(widget));
	object = parse_wavefront_file(ui->selected_obj.object->filename);
	if (!object)
	{
		dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			"Can not load %s.\nAn error occured.\n%s",
			ui->selected_obj.object->filename, g_strerror(errno));
		g_signal_connect_swapped(dialog, "response", G_CALLBACK(
			gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		ui->selected_obj.object->nb_faces = 0;
		ui->selected_obj.object->faces = 0;
		return ;
	}
	ui->selected_obj.object->nb_faces = object->nb_faces;
	ui->selected_obj.object->faces = object->faces;
}

void			add_objext_widgets(t_ui *ui, t_object *focused_obj,
															GtkWidget *props)
{
	GtkWidget	*file_chooser;

	file_chooser = gtk_file_chooser_button_new(".obj Wavefront model file",
												GTK_FILE_CHOOSER_ACTION_OPEN);
	if (focused_obj->filename)
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser),
														focused_obj->filename);
	g_signal_connect(file_chooser, "file-set",
											G_CALLBACK(wavefront_file_set), ui);
	gtk_container_add(GTK_CONTAINER(props), gtk_label_new("Model .obj"));
	gtk_container_add(GTK_CONTAINER(props), file_chooser);
}
