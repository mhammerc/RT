#include "ui.h"
#include "converter.h"

void		init_cam(t_ui *ui)
{
	t_ui_cam	*cam;

	cam = (t_ui_cam*)malloc(sizeof(t_cam));
	if(!cam)
		exit(EXIT_FAILURE);
	ft_bzero(cam, sizeof(t_cam));
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 7;
	cam->dir.x = 0;
	cam->dir.y = 0;
	cam->dir.z = 0;
	ui->cam = cam;
}

static void		cam_edited()
{
	t_ui		*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

static void		pos_edited(GtkWidget *widget, t_vec3 *pos, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->pos = *pos;
	free(pos);
	cam_edited();
}

static void		dir_edited(GtkWidget *widget, t_vec3 *dir, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->dir = *dir;
	free(dir);
	cam_edited();
}

void		edit_cam_properties(gpointer data)
{
	t_ui		*view;

	view = (t_ui*)data;
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), gtk_label_new_with_mnemonic("_Camera"));
	GtkWidget	*pos = create_vector3_entry("pos		", view->cam->pos);
	GtkWidget	*lkat = create_vector3_entry("LookAt	", view->cam->dir);
	g_signal_connect(pos, "rt-vector3-entry-edited", G_CALLBACK(pos_edited), view);
	g_signal_connect(lkat, "rt-vector3-entry-edited", G_CALLBACK(dir_edited), view);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), pos);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), lkat);

	gtk_widget_show_all(view->window);
}
