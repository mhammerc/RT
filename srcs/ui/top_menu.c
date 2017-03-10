#include "widget.h"
#include "ui.h"
#include "converter.h"

static void				toggle_render_on_change(GtkCheckMenuItem *checkmenuitem, gpointer user_data)
{
	t_ui	*ui;

	ui = get_interface();
	ui->render_on_change = gtk_check_menu_item_get_active(checkmenuitem);
}

static void				render_new_image()
{
	t_ui	*ui;

	ui = get_interface();
	ask_for_new_image(ui);
}

static t_menu_file		*create_file_menu(void)
{
	t_menu_file		*file_menu;

	file_menu = (t_menu_file *)malloc(sizeof(t_menu_file));
	file_menu->menu = gtk_menu_new();
	file_menu->open = gtk_menu_item_new_with_label("Open");
	file_menu->save = gtk_menu_item_new_with_label("Save scene");
	file_menu->export = gtk_menu_item_new_with_label("Export as PNG");
	file_menu->quit = gtk_menu_item_new_with_label("Quit");
	file_menu->render_on_change = gtk_check_menu_item_new_with_label("Render scene on every change");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(file_menu->render_on_change), TRUE);
	file_menu->start_render = gtk_menu_item_new_with_label("Render the scene");
	g_signal_connect(file_menu->export, "activate",
		G_CALLBACK (open_dialog_save), NULL);
	g_signal_connect(file_menu->render_on_change, "activate", G_CALLBACK(toggle_render_on_change), NULL);
	g_signal_connect(file_menu->start_render, "activate", G_CALLBACK(render_new_image), NULL);
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
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->render_on_change);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), file_menu->start_render);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), top_menu, FALSE, FALSE, 0);
	return (box);
}
