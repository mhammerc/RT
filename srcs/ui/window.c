#include "ui.h"
#include <locale.h>

static GtkWidget		*create_app_window(GtkApplication *app, int width, int height,
	char *title)
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

t_ui	*get_interface()
{
	static t_ui	ui = {};

	return (&ui);
}

void			setup_custom_signals()
{
	g_signal_new("rt-entry-edited",
			G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
			0, NULL, NULL,
			g_cclosure_marshal_VOID__POINTER,
			G_TYPE_NONE, 1, G_TYPE_STRING);
	g_signal_new("rt-scale-entry-edited",
			G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
			0, NULL, NULL,
			g_cclosure_marshal_VOID__DOUBLE,
			G_TYPE_NONE, 1, G_TYPE_DOUBLE);
	g_signal_new("rt-numeric-entry-edited",
			G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
			0, NULL, NULL,
			g_cclosure_marshal_VOID__DOUBLE,
			G_TYPE_NONE, 1, G_TYPE_DOUBLE);
	g_signal_new("rt-vector3-entry-edited",
			G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
			0, NULL, NULL,
			g_cclosure_marshal_VOID__POINTER,
			G_TYPE_NONE, 1, G_TYPE_POINTER);
}

void			build_interface(GtkApplication *app, gpointer user_data)
{
	t_ui			*ui;
	int				*index;

	setlocale(LC_ALL, "C");
	ui = get_interface();
	(void)user_data;
	pthread_mutex_init(&ui->mutex_stock, NULL);
	ui->lp = (t_left_panel*)malloc(sizeof(t_left_panel));
	ui->dp = (t_display_panel*)malloc(sizeof(t_display_panel));
	ui->rp = (t_right_panel*)malloc(sizeof(t_right_panel));
	ui->render_on_change = TRUE;
	index = (int*)malloc(sizeof(int) * 50);
	if (!index)
		exit (EXIT_FAILURE);
	ui->selected_obj.index = index;
	setup_custom_signals();

	ui->window = create_app_window(app, 0, 0, "RT by The Most Awesome Group");
	ui->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	ui->top_menu = create_top_menu();
	ui->workspace = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	ui->progress_bar = gtk_progress_bar_new();
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
