#include "ui.h"

void		init_scene(t_ui *ui)
{
}


static void		scene_edited()
{
	t_ui	*ui;

	ui = get_interface();
	ui->rp->scene_gtk.fxaa = atoi(gtk_entry_get_text(GTK_ENTRY(ui->rp->scene_gtk.fxaa_scale_entry)));
	if (ui->render_on_change)
		ask_for_new_image(ui);
	--ui->lock;
}



void		edit_scene_properties(gpointer data)
{
	t_ui		*ui;

	ui = (t_ui*)data;

	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), gtk_label_new_with_mnemonic("_Scene"));
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), create_scale_entry("FXAA", ui->rp->scene_gtk.fxaa, &ui->rp->scene_gtk.fxaa_scale_entry, scene_edited));
}
