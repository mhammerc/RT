#include "ui.h"

void		init_scene(t_ui *ui)
{
//	t_scene *scene;
//	scene = (t_scene*)malloc(sizeof(t_scene));
//	if(!scene)
//		exit(EXIT_FAILURE);
//	ui->scene = scene;
}


static void		scene_edited()
{
	t_scene	*scene;
	t_ui	*ui;
	ui = get_interface();
//	scene = ui->scene;
//	scene->nb_obj = 50;
	ui->rp->scene_gtk.nb_obj = GTK_WIDGET(15);
//	scene->pos.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.pos.y)));
//	scene->pos.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.pos.z)));
//	scene->lkat.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.lkat.x)));
//	scene->lkat.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.lkat.y)));
//	scene->lkat.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.lkat.z)));
}



void		edit_scene_properties(gpointer data)
{
	t_ui		*view;
//	t_scene		*scene;

	view = (t_ui*)data;
//	view->scene->nb_obj = 3; //a actualiser en continue

	gtk_container_add(GTK_CONTAINER(view->rp->scene_prop), gtk_label_new_with_mnemonic("_Scene"));
	GtkWidget	*nb_obj = gtk_label_new(ft_itoa(17));//penser a free
//	gtk_label_set_text (GTK_LABEL(nb_obj), "nb_obj");
//	GtkWidget	*nb_obj =create_numeric_entry("nb_obj", view->scene->nb_obj, &(view->rp->scene_gtk.nb_obj), scene_edited);
//	GtkWidget	*lkat = create_vector3_entry("LookAt", view->scene->lkat, &view->rp->scene_gtk.lkat, scene_edited);
	gtk_container_add(GTK_CONTAINER(view->rp->scene_prop), nb_obj);
//	gtk_container_add(GTK_CONTAINER(view->rp->scene_prop), lkat);

	gtk_widget_show_all(view->window);
}
