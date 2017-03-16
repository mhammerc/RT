#include "ui.h"

void		right_panel(t_ui *ui, t_right_panel *rp)
{
	init_cam(ui);
	init_scene(ui);
	rp->right_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(ui->workspace), rp->right_panel);

	rp->el_prop_lst = gtk_list_box_new();
	gtk_widget_set_size_request(rp->el_prop_lst, 280, 300);

	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->el_prop_lst);
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(ui->lp->tree.tree),
																		TRUE);

	rp->cam_prop = gtk_list_box_new();
	gtk_widget_set_size_request(rp->cam_prop, 280, 200);

	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->cam_prop);
	edit_cam_properties(ui);

	rp->scene_prop = gtk_list_box_new();
	gtk_widget_set_size_request(rp->scene_prop, 280, 200);

	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->scene_prop);

	/*rp->color_chooser = gtk_list_box_new();
	gtk_widget_set_size_request(rp->color_chooser, 280, 200);

	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->color_chooser);
	edit_color(ui);*/
	edit_scene_properties(ui);
}
