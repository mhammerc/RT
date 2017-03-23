/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:48:48 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 16:18:48 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void				toggle_render_on_change(GtkCheckMenuItem *checkmenuitem,
							gpointer user_data)
{
	t_ui	*ui;

	ui = get_interface();
	(void)user_data;
	ui->render_on_change = gtk_check_menu_item_get_active(checkmenuitem);
}

static void				render_new_image(void)
{
	t_ui	*ui;

	ui = get_interface();
	ask_for_new_image(ui);
}

static void				exit_rt(void)
{
	ft_exit_fd("Closing RT.", 1);
}

static t_menu_file		*create_file_menu(void)
{
	t_menu_file		*fmenu;

	fmenu = (t_menu_file *)monloc(sizeof(t_menu_file));
	fmenu->menu = gtk_menu_new();
	fmenu->open = gtk_menu_item_new_with_label("Open (F1)");
	fmenu->save = gtk_menu_item_new_with_label("Save scene (F2)");
	fmenu->export = gtk_menu_item_new_with_label("Export as PNG (F3)");
	fmenu->quit = gtk_menu_item_new_with_label("Quit (ESC)");
	fmenu->render_on_change =
			gtk_check_menu_item_new_with_label("Render scene on every change");
	gtk_check_menu_item_set_active(
						GTK_CHECK_MENU_ITEM(fmenu->render_on_change), TRUE);
	fmenu->start_render = gtk_menu_item_new_with_label("Render the scene");
	g_signal_connect(fmenu->open, "activate",
		G_CALLBACK(open_dialog_open), NULL);
	g_signal_connect(fmenu->save, "activate",
		G_CALLBACK(open_dialog_save), NULL);
	g_signal_connect(fmenu->export, "activate",
		G_CALLBACK(open_dialog_export), NULL);
	g_signal_connect(fmenu->quit, "activate", G_CALLBACK(exit_rt), NULL);
	g_signal_connect(fmenu->render_on_change, "activate",
									G_CALLBACK(toggle_render_on_change), NULL);
	g_signal_connect(fmenu->start_render, "activate",
									G_CALLBACK(render_new_image), NULL);
	return (fmenu);
}

GtkWidget				*create_top_menu(void)
{
	GtkWidget		*top_menu;
	GtkWidget		*box;
	t_ui			*ui;

	ui = get_interface();
	top_menu = gtk_menu_bar_new();
	ui->file_menu = create_file_menu();
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), ui->file_menu->open);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), ui->file_menu->save);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), ui->file_menu->export);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu), ui->file_menu->quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu),
											ui->file_menu->render_on_change);
	gtk_menu_shell_append(GTK_MENU_SHELL(top_menu),
											ui->file_menu->start_render);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(box), top_menu, FALSE, FALSE, 0);
	return (box);
}
