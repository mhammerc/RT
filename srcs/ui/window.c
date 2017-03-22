/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:47:12 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:08:40 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static GtkWidget	*create_app_window(GtkApplication *app, int width,
							int height, char *title)
{
	GtkWidget	*win;

	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), title);
	gtk_window_set_default_size(GTK_WINDOW(win), width, height);
	gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
	return (win);
}

static void			default_scene(t_ui *ui)
{
	create_sphere(FALSE);
	create_light(FALSE);
	refresh_obj_tree(ui);
}

static void			setup_custom_signals(void)
{
	g_signal_new("rt-entry-edited", G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST, 0, NULL,
		NULL, g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_STRING);
	g_signal_new("rt-scale-entry-edited", G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST, 0,
		NULL, NULL, g_cclosure_marshal_VOID__DOUBLE, G_TYPE_NONE, 1,
		G_TYPE_DOUBLE);
	g_signal_new("rt-numeric-entry-edited", G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
		0, NULL, NULL, g_cclosure_marshal_VOID__DOUBLE, G_TYPE_NONE, 1,
		G_TYPE_DOUBLE);
	g_signal_new("rt-vector3-entry-edited", G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
		0, NULL, NULL, g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1,
		G_TYPE_POINTER);
}

static void			build_interface(t_ui *ui)
{
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress_bar), 0.);
	gtk_container_add(GTK_CONTAINER(ui->window), ui->main_box);
	gtk_container_add(GTK_CONTAINER(ui->main_box), ui->top_menu);
	gtk_container_add(GTK_CONTAINER(ui->main_box), ui->workspace);
	gtk_container_add(GTK_CONTAINER(ui->main_box), ui->progress_bar);
	left_panel(ui, ui->lp);
	display_panel(ui, ui->dp);
	right_panel(ui, ui->rp);
	default_scene(ui);
	event_handler_window(ui);
	event_handler_display(ui);
	gtk_widget_show_all(ui->window);
}

void				init_interface(GtkApplication *app, gpointer user_data)
{
	t_ui	*ui;
	int		*index;

	(void)user_data;
	setlocale(LC_ALL, "C");
	ui = get_interface();
	pthread_mutex_init(&ui->mutex_stock, NULL);
	setup_custom_signals();
	index = (int*)malloc(sizeof(int) * 50);
	ui->lp = (t_left_panel*)malloc(sizeof(t_left_panel));
	ui->dp = (t_display_panel*)malloc(sizeof(t_display_panel));
	ui->rp = (t_right_panel*)malloc(sizeof(t_right_panel));
	ui->percent = (double*)malloc(sizeof(double));
	ui->selected_obj.index = index;
	ui->render_on_change = TRUE;
	ui->window = create_app_window(app, 0, 0, "RT by The Most Awesome Group");
	ui->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	ui->top_menu = create_top_menu();
	ui->workspace = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	ui->progress_bar = gtk_progress_bar_new();
	build_interface(ui);
}
