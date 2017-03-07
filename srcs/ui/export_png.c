#include <ui.h>

static void		export_png (char *filename)
{
	GError		*error;
	GdkPixbuf	*ref;
	GdkPixbuf	*pixbuf;
	t_ui		*ui;

	error = NULL;
	ui = get_interface();
	gdk_pixbuf_save (ui->dp->pixbuf, filename, "png", &error, NULL);
	g_assert_no_error (error);
}

void			open_dialog_save(void)
{
	GtkWidget				*dialog;
	GtkFileChooser 			*chooser;
	GtkFileChooserAction	action;
	gint					res;
	char 					*filename;
	t_ui					*ui;

	ui = get_interface();
	action = GTK_FILE_CHOOSER_ACTION_SAVE;
	dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(ui->window),
		action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT,
		NULL);
	chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
	res = gtk_dialog_run (GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(chooser);
		export_png(filename);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}
