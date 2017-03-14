
#include "ui.h"

static void		obj_pos_rot_key(t_ui *ui, GdkEventKey *event)
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
	else
		return ;
	ask_for_new_image(ui);
}

static void		cam_pos_rot_key(t_ui *ui, GdkEventKey *event)
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
	else
		return ;
	ask_for_new_image(ui);
}

static void		other_key(t_ui *ui, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Delete)
		del_obj_btn(NULL, ui);
	else if (event->keyval == GDK_KEY_Insert)
		add_obj_btn(NULL, ui);
	else
		return ;
	ask_for_new_image(ui);
}

static int		on_key_press_display(GtkWidget *widget, GdkEventKey *event,
															gpointer user_data)
{
	t_ui	*ui;

	ui = get_interface();
	(void)widget;
	(void)user_data;
	if (ui->selected_obj.object && event->keyval != GDK_KEY_Delete && event->keyval != GDK_KEY_Delete)
		obj_pos_rot_key(ui, event);
	else if (!ui->selected_obj.object)
		cam_pos_rot_key(ui, event);
	else
		other_key(ui, event);
	return (FALSE);
}

void			event_handler_display(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->lp->tree.tree), "key_press_event",
										G_CALLBACK(on_key_press_display), NULL);
}
