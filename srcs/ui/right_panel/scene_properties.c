#include "ui.h"

void		init_scene(t_ui *ui)
{
	ui->rp->scene_gtk.ambiant_light = 0.42;
	ui->rp->scene_gtk.fov = 45;
}


static void		scene_edited()
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

static void		fxaa_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.fxaa = value;
	scene_edited();
}

static void		ambiant_light_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.ambiant_light = value;
	scene_edited();
}

static void		fov_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.fov = value;
	scene_edited();
}

void			edit_scene_properties(gpointer data)
{
	t_ui		*ui;
	GtkWidget	*fxaa;
	GtkWidget	*ambiant_light;
	GtkWidget	*fov;

	ui = (t_ui*)data;

	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), gtk_label_new_with_mnemonic("_Scene"));

	ambiant_light = create_scale_entry("Ambiant Light", ui->rp->scene_gtk.ambiant_light, 0, 1);
	g_signal_connect(ambiant_light, "rt-scale-entry-edited", G_CALLBACK(ambiant_light_edited), ui);

	fov = create_scale_entry("FOV", ui->rp->scene_gtk.fov, 45, 90);
	g_signal_connect(fov, "rt-scale-entry-edited", G_CALLBACK(fov_edited), ui);

	fxaa = create_scale_entry("FXAA", ui->rp->scene_gtk.fxaa, 0, 16);
	g_signal_connect(fxaa, "rt-scale-entry-edited", G_CALLBACK(fxaa_edited), ui);

	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), ambiant_light);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), fov);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), fxaa);
}
