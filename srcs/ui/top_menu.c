#include "widget.h"
#include "ui.h"

static	t_menu_file		*create_file_menu(void)
{
	t_menu_file		*file_menu;

	file_menu = (t_menu_file *)malloc(sizeof(t_menu_file));
	file_menu->menu = gtk_menu_new();
	file_menu->open = gtk_menu_item_new_with_label("Open");
	file_menu->save = gtk_menu_item_new_with_label("Save scene");
	file_menu->export = gtk_menu_item_new_with_label("Export as PNG");
	file_menu->quit = gtk_menu_item_new_with_label("Quit");
	g_signal_connect (file_menu->export, "activate",
		G_CALLBACK (open_dialog_save), NULL);
	return (file_menu);
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
