#include "ui.h"

static void				exit_rt(void)
{
	ft_exit_fd("Closing RT.", 1);
}

static void		export_png(char *filename)
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

void			open_dialog_open(void)
{
	GtkWidget				*dialog;
	GtkFileChooser 			*chooser;
	GtkFileChooserAction	action;
	gint					res;
	char 					*filename;
	t_ui					*ui;

	ui = get_interface();
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(ui->window),
		action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT,
		NULL);
	chooser = GTK_FILE_CHOOSER(dialog);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(chooser);
		load_file(filename);
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}

void			open_dialog_save(void)
{
	GtkWidget				*dialog;
	GtkFileChooser 			*chooser;
	GtkFileChooserAction	action;
	gint					res;
	char 					*filename;
	// t_ui					*ui;
	//
	// ui = get_interface();
	// action = GTK_FILE_CHOOSER_ACTION_SAVE;
	// dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(ui->window),
	// 	action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT,
	// 	NULL);
	// chooser = GTK_FILE_CHOOSER (dialog);
	// gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
	// res = gtk_dialog_run (GTK_DIALOG(dialog));
	// if (res == GTK_RESPONSE_ACCEPT)
	// {
	// 	filename = gtk_file_chooser_get_filename(chooser);
		ft_printf("Can't save yet, parser coming soon(ish)!\n");
	// 	g_free (filename);
	// }
	// gtk_widget_destroy (dialog);
}

void			open_dialog_export(void)
{
	GtkWidget				*dialog;
	GtkFileChooser 			*chooser;
	GtkFileChooserAction	action;
	gint					res;
	char 					*filename;
	t_ui					*ui;

	ui = get_interface();
	action = GTK_FILE_CHOOSER_ACTION_SAVE;
	dialog = gtk_file_chooser_dialog_new("Export File", GTK_WINDOW(ui->window),
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
	gtk_widget_destroy(dialog);
}

static	t_menu_file		*create_file_menu(void)
{
	t_ui	*ui;

	ui = get_interface();
	ui->file_menu = (t_menu_file *)malloc(sizeof(t_menu_file));
	ui->file_menu->menu = gtk_menu_new();
	ui->file_menu->open = gtk_menu_item_new_with_label("Open (F1)");
	ui->file_menu->save = gtk_menu_item_new_with_label("Save scene (F2)");
	ui->file_menu->export = gtk_menu_item_new_with_label("Export as PNG (F3)");
	ui->file_menu->quit = gtk_menu_item_new_with_label("Quit (ESC)");
	g_signal_connect(ui->file_menu->open, "activate",
		G_CALLBACK (open_dialog_open), NULL);
	g_signal_connect(ui->file_menu->save, "activate",
		G_CALLBACK (open_dialog_save), NULL);
	g_signal_connect(ui->file_menu->export, "activate",
		G_CALLBACK (open_dialog_export), NULL);
	g_signal_connect(ui->file_menu->quit, "activate",
		G_CALLBACK (exit_rt), NULL);
	return (ui->file_menu);
}

GtkWidget				*create_top_menu(void)
{
	GtkWidget		*top_menu;
	GtkWidget		*box;
	t_menu_file		*file_menu;

	top_menu = gtk_menu_bar_new();
	file_menu = create_file_menu();
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->open);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->save);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->export);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->quit);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), top_menu, FALSE, FALSE, 0);
	return (box);
}
