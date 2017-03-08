#include "ui.h"


static int		on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	t_ui	*ui;

	ui = get_interface();
	if (event->keyval == GDK_KEY_Escape)
		ft_exit_fd("Closing RT.", 1);
	else if (event->keyval == GDK_KEY_w)
		printf("w key pressed\n");
	else if (event->keyval == GDK_KEY_a)
		printf("a key pressed\n");
	else if (event->keyval == GDK_KEY_s)
		printf("s key pressed\n");
	else if (event->keyval == GDK_KEY_d)
		printf("d key pressed\n");
	else if (event->keyval == GDK_KEY_q)
		printf("q key pressed\n");
	else if (event->keyval == GDK_KEY_e)
		printf("e key pressed\n");
	else if (event->keyval == GDK_KEY_W)
		printf("W key pressed\n");
	else if (event->keyval == GDK_KEY_A)
		printf("A key pressed\n");
	else if (event->keyval == GDK_KEY_S)
		printf("S key pressed\n");
	else if (event->keyval == GDK_KEY_D)
		printf("D key pressed\n");
	else if (event->keyval == GDK_KEY_Q)
		printf("Q key pressed\n");
	else if (event->keyval == GDK_KEY_E)
		printf("E key pressed\n");
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
	// else if (event->keyval == GDK_KEY_Return)
	// 	printf("Return key pressed\n");
	// else if (event->keyval == GDK_KEY_Up)
	// 	printf("Up key pressed\n");
	// else if (event->keyval == GDK_KEY_Down)
	// 	printf("Down key pressed\n");
	// else if (event->keyval == GDK_KEY_Left)
	// 	printf("Left key pressed\n");
	// else if (event->keyval == GDK_KEY_Right)
	// 	printf("Right key pressed\n");
	return (FALSE);
}

// static int		on_mouse_scroll(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)
// {
// 	if (GDK_SCROLL)
// 		printf("SCROLL DOWN\n");
// 	else if (GDK_SCROLL)
// 		printf("SCROLL UP\n");
// 	return (FALSE);
// }
//
void			event_handler(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->window), "key_press_event", G_CALLBACK(on_key_press), NULL);
	// g_signal_connect(G_OBJECT(ui->window), "scroll-event", G_CALLBACK(on_mouse_scroll), NULL);
}
