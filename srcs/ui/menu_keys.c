#include "ui.h"

static void		menu_keys(GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
		ft_exit_fd("Closing RT.", 1);
	else if (event->keyval == GDK_KEY_F1)
		open_dialog_open();
	else if (event->keyval == GDK_KEY_F2)
		open_dialog_save();
	else if (event->keyval == GDK_KEY_F3)
		open_dialog_export();
	else if (event->keyval == GDK_KEY_F4)
		printf("F4 key pressed\n");
	else if (event->keyval == GDK_KEY_F5)
		printf("F5 key pressed\n");
}

static int		on_key_press_window(GtkWidget *widget, GdkEventKey *event,
					gpointer user_data)
{
	t_ui		*ui;

	ui = get_interface();
	(void)widget;
	(void)user_data;
	menu_keys(event);
	return (FALSE);
}

void			event_handler_window(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->window), "key_press_event",
		G_CALLBACK(on_key_press_window), NULL);
}
