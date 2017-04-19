/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialogs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:18:27 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/12 10:41:53 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void			open_dialog_open(void)
{
	t_ui					*ui;
	GtkWidget				*dialog;
	gint					res;
	char					*filename;

	ui = get_interface();
	clear_properties_list(ui);
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(ui->window),
				GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL,
				"_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		load_file(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

void			open_dialog_save(void)
{
	t_ui					*ui;
	GtkWidget				*dialog;
	GtkFileChooser			*chooser;
	gint					res;
	char					*filename;

	ui = get_interface();
	dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(ui->window),
				GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
				"_Save", GTK_RESPONSE_ACCEPT, NULL);
	chooser = GTK_FILE_CHOOSER(dialog);
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(chooser);
		save_scene(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

static void		export_png(char *filename)
{
	GError		*error;
	t_ui		*ui;

	error = NULL;
	ui = get_interface();
	gdk_pixbuf_save(ui->dp->pixbuf, filename, "png", &error, NULL);
	g_assert_no_error(error);
}

void			open_dialog_export(void)
{
	t_ui					*ui;
	GtkWidget				*dialog;
	GtkFileChooser			*chooser;
	gint					res;
	char					*filename;

	ui = get_interface();
	dialog = gtk_file_chooser_dialog_new("Export File", GTK_WINDOW(ui->window),
				GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
				"_Save", GTK_RESPONSE_ACCEPT, NULL);
	chooser = GTK_FILE_CHOOSER(dialog);
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(chooser);
		export_png(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}
