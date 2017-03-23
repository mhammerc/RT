/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_panel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:32:59 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 11:18:55 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		right_panel(t_ui *ui, t_right_panel *rp)
{
	init_cam(ui);
	init_scene(ui);
	rp->right_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(ui->workspace), rp->right_panel);
	rp->el_prop_lst = gtk_list_box_new();
	gtk_widget_set_size_request(rp->el_prop_lst, 277, 560);
	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->el_prop_lst);
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(ui->lp->tree.tree),
		TRUE);
	rp->cam_prop = gtk_list_box_new();
	gtk_widget_set_size_request(rp->cam_prop, 277, 150);
	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->cam_prop);
	edit_cam_properties(ui);
	rp->scene_prop = gtk_list_box_new();
	gtk_widget_set_size_request(rp->scene_prop, 277, 190);
	gtk_container_add(GTK_CONTAINER(rp->right_panel), rp->scene_prop);
	edit_scene_properties(ui);
}
