#include "ui.h"

GtkWidget	*create_float3_entry(gchar *name, cl_float3 value, t_vector3w *ref, void *signal);

void		init_cam(t_ui *ui)
{
	t_cam *cam;
	cam = (t_cam*)malloc(sizeof(t_cam));
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
	t_cam	*cam;
	t_ui	*ui;

	ui = get_interface();
	cam = ui->cam;
	cam->pos.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.pos.x)));
	cam->pos.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.pos.y)));
	cam->pos.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.pos.z)));

	cam->dir.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.lkat.x)));
	cam->dir.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.lkat.y)));
	cam->dir.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->cam_gtk.lkat.z)));
}

void		edit_cam_properties(gpointer data)
{
	t_ui		*view;
	t_cam		*cam;

	view = (t_ui*)data;

	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), gtk_label_new_with_mnemonic("_Camera"));
	GtkWidget	*pos = create_float3_entry("pos		", view->cam->pos, &view->rp->cam_gtk.pos, cam_edited);
	GtkWidget	*lkat = create_float3_entry("LookAt	", view->cam->dir, &view->rp->cam_gtk.lkat, cam_edited);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), pos);
	gtk_container_add(GTK_CONTAINER(view->rp->cam_prop), lkat);

	gtk_widget_show_all(view->window);
}
