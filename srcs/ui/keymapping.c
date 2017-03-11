
#include "ui.h"

static void		top_menu_key(t_ui *ui, GdkEventKey *event)
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

static void		obj_pos_rot_key(t_ui *ui, int mod, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_w)
		ui->selected_obj.object->pos.y += 0.1;
	else if (event->keyval == GDK_KEY_a)
		ui->selected_obj.object->pos.x -= 0.1;
	else if (event->keyval == GDK_KEY_s)
		ui->selected_obj.object->pos.y -= 0.1;
	else if (event->keyval == GDK_KEY_d)
		ui->selected_obj.object->pos.x += 0.1;
	else if (event->keyval == GDK_KEY_q)
		ui->selected_obj.object->pos.z -= 0.2;
	else if (event->keyval == GDK_KEY_e)
		ui->selected_obj.object->pos.z += 0.2;
	else if (event->keyval == GDK_KEY_W)
		ui->selected_obj.object->rot.y += 0.1;
	else if (event->keyval == GDK_KEY_A)
		ui->selected_obj.object->rot.x -= 0.1;
	else if (event->keyval == GDK_KEY_S)
		ui->selected_obj.object->rot.y -= 0.1;
	else if (event->keyval == GDK_KEY_D)
		ui->selected_obj.object->rot.x += 0.1;
	else if (event->keyval == GDK_KEY_Q)
		ui->selected_obj.object->rot.z -= 0.1;
	else if (event->keyval == GDK_KEY_E)
		ui->selected_obj.object->rot.z += 0.1;
}

static void		cam_pos_rot_key(t_ui *ui, int mod, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_w)
		ui->cam->pos.y += 0.1;
	else if (event->keyval == GDK_KEY_a)
		ui->cam->pos.x -= 0.1;
	else if (event->keyval == GDK_KEY_s)
		ui->cam->pos.y -= 0.1;
	else if (event->keyval == GDK_KEY_d)
		ui->cam->pos.x += 0.1;
	else if (event->keyval == GDK_KEY_q)
		ui->cam->pos.z -= 0.1;
	else if (event->keyval == GDK_KEY_e)
			ui->cam->pos.z += 0.1;
	else if (event->keyval == GDK_KEY_W)
		ui->cam->dir.y += 0.1;
	else if (event->keyval == GDK_KEY_A)
		ui->cam->dir.x -= 0.1;
	else if (event->keyval == GDK_KEY_S)
		ui->cam->dir.y -= 0.1;
	else if (event->keyval == GDK_KEY_D)
			ui->cam->dir.x += 0.1;
	else if (event->keyval == GDK_KEY_Q)
		ui->cam->dir.z -= 0.1;
	else if (event->keyval == GDK_KEY_E)
		ui->cam->dir.z += 0.1;
}

// static void		other_obj_relative_keys(t_ui *ui, int mod, GdkEventKey *event)
// {
// 	if (event->keyval == GDK_KEY_u)
// 		// ui->selected_obj.object; A DESELECTIONER
// }

static int		on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	t_ui	*ui;
	int		mod;

	mod = 0;
	ui = get_interface();
	top_menu_key(ui, event);
	if (ui->selected_obj.object)
		obj_pos_rot_key(ui, mod, event);
	else if (!ui->selected_obj.object)
	{
		cam_pos_rot_key(ui, mod, event);
	}
	// other_obj_relative_keys(ui, mod, event);
	ask_for_new_image(ui);
	return (FALSE);
}

void			event_handler(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->window), "key_press_event", G_CALLBACK(on_key_press), NULL);
	// g_signal_connect(G_OBJECT(ui->window), "scroll-event", G_CALLBACK(on_mouse_scroll), NULL);
}

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

// static int		on_mouse_scroll(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)
// {
// 	if (GDK_SCROLL)
// 		printf("SCROLL DOWN\n");
// 	else if (GDK_SCROLL)
// 		printf("SCROLL UP\n");
// 	return (FALSE);
// }
//
