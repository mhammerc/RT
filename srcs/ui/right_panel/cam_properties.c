#include "ui.h"
#include "converter.h"

void		init_cam(t_ui *ui)
{
	t_ui_cam	*cam;

	cam = (t_ui_cam*)malloc(sizeof(t_cam));
	if(!cam)
		exit(EXIT_FAILURE);
	ft_bzero(cam, sizeof(t_cam));
	cam->pos = (t_vec3){0., 0., 7.};
	cam->dir = (t_vec3){0., 0., 0.};
	cam->up = (t_vec3){0., 1., 0.};
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

static void		up_edited(GtkWidget *widget, t_vec3 *up, gpointer data)
{
	t_ui	*ui;

	(void)widget;
	ui = (t_ui*)data;
	ui->cam->up = *up;
	free(up);
	cam_edited();
}

void		edit_cam_properties(gpointer data)
{
	t_ui		*view;

	view = (t_ui*)data;
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop),
		gtk_label_new_with_mnemonic("_Camera"));
	view->rp->pos = create_vector3_entry("pos		", view->cam->pos);
	view->rp->lkat = create_vector3_entry("LookAt	", view->cam->dir);
	view->rp->up = create_vector3_entry("Up           ", view->cam->up);
	g_signal_connect(view->rp->pos, "rt-vector3-entry-edited",
		G_CALLBACK(pos_edited), view);
	g_signal_connect(view->rp->lkat, "rt-vector3-entry-edited",
		G_CALLBACK(dir_edited), view);
	g_signal_connect(view->rp->up, "rt-vector3-entry-edited",
		G_CALLBACK(up_edited), view);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->pos);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->lkat);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), view->rp->up);
	gtk_widget_show_all(view->window);
}

void 		refresh_cam_properties(t_ui *ui)
{
	GList		*children;
	GList		*iter;

	children = gtk_container_get_children(GTK_CONTAINER(ui->rp->cam_prop));
	iter = children;
	while (iter)
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));
		iter = g_list_next(iter);
	}
	g_list_free(children);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop),
		gtk_label_new_with_mnemonic("_Camera"));
	ui->rp->pos = create_vector3_entry("pos		", ui->cam->pos);
	ui->rp->lkat = create_vector3_entry("LookAt	", ui->cam->dir);
	ui->rp->up = create_vector3_entry("Up           ", ui->cam->up);
	g_signal_connect(ui->rp->pos, "rt-vector3-entry-edited",
		G_CALLBACK(pos_edited), ui);
	g_signal_connect(ui->rp->lkat, "rt-vector3-entry-edited",
		G_CALLBACK(dir_edited), ui);
	g_signal_connect(ui->rp->up, "rt-vector3-entry-edited",
		G_CALLBACK(up_edited), ui);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->pos);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->lkat);
	gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->up);
	gtk_widget_show_all(ui->rp->cam_prop);
}
