/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:15:34 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/22 17:21:50 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void		make_lock(void)
{
	get_interface()->lock3 = 1;
}

static void		button_relase(GtkWidget *widget, GdkEvent *event,
					gpointer user_data)
{
	t_ui		*ui;

	(void)event;
	ui = (t_ui*)user_data;
	if (ui->lock3)
	{
		--ui->lock3;
		return ;
	}
	gtk_tree_selection_unselect_all(gtk_tree_view_get_selection(
		GTK_TREE_VIEW(widget)));
	clear_properties_list(ui);
	ui->selected_obj.object = NULL;
}

static void		left_panel_btn(t_ui *ui, t_left_panel *lp)
{
	lp->lp_btns.add_obj = gtk_button_new_with_label("OBJ");
	lp->lp_btns.add_light = gtk_button_new_with_label("LIGHT");
	lp->lp_btns.cpy = gtk_button_new_with_label("COPY");
	lp->lp_btns.remove = gtk_button_new_with_label("DEL");
	gtk_widget_set_size_request(lp->lp_btns.add_obj, 70, 0);
	gtk_widget_set_size_request(lp->lp_btns.add_light, 70, 0);
	gtk_widget_set_size_request(lp->lp_btns.remove, 70, 0);
	gtk_container_add(GTK_CONTAINER(lp->lp_btns.button), lp->lp_btns.add_obj);
	gtk_container_add(GTK_CONTAINER(lp->lp_btns.button), lp->lp_btns.add_light);
	gtk_container_add(GTK_CONTAINER(lp->lp_btns.button), lp->lp_btns.remove);
	gtk_container_add(GTK_CONTAINER(lp->lp_btns.button), lp->lp_btns.cpy);
	g_signal_connect(lp->lp_btns.add_obj, "clicked",
		G_CALLBACK(add_obj_btn), ui);
	g_signal_connect(lp->lp_btns.add_light, "clicked",
		G_CALLBACK(add_light_btn), ui);
	g_signal_connect(lp->lp_btns.remove, "clicked",
		G_CALLBACK(del_obj_btn), ui);
	g_signal_connect(lp->lp_btns.cpy, "clicked", G_CALLBACK(cpy_obj_btn), ui);
}

static void		left_panel_tree(t_ui *ui, t_left_panel *lp)
{
	lp->tree.store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	lp->tree.tree = gtk_tree_view_new_with_model(
		GTK_TREE_MODEL(lp->tree.store));
	lp->tree.renderer = gtk_cell_renderer_text_new();
	lp->tree.col_el = gtk_tree_view_column_new_with_attributes("Element",
		lp->tree.renderer, "text", 0, NULL);
	lp->tree.col_type = gtk_tree_view_column_new_with_attributes("Type",
		lp->tree.renderer, "text", 1, NULL);
	g_signal_connect(ui->lp->tree.tree, "row-activated",
		G_CALLBACK(edit_element_properties), ui);
	g_signal_connect(ui->lp->tree.tree, "cursor-changed",
		G_CALLBACK(make_lock), ui);
	g_signal_connect_after(GTK_SCROLLABLE(lp->tree.tree),
		"button-release-event", G_CALLBACK(button_relase), ui);
	gtk_widget_set_size_request(lp->tree.tree, 277, 735);
	gtk_tree_view_append_column(GTK_TREE_VIEW(lp->tree.tree), lp->tree.col_el);
	gtk_tree_view_append_column(GTK_TREE_VIEW(lp->tree.tree),
		lp->tree.col_type);
}

void			left_panel(t_ui *ui, t_left_panel *lp)
{
	GtkWidget		*scroll;

	lp->lp_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	lp->lp_btns.button = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	left_panel_tree(ui, lp);
	left_panel_btn(ui, lp);
	gtk_container_add(GTK_CONTAINER(ui->workspace), lp->lp_box);
	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(scroll, 277, 735);
	gtk_container_add(GTK_CONTAINER(scroll), lp->tree.tree);
	gtk_container_add(GTK_CONTAINER(lp->lp_box), lp->lp_btns.button);
	gtk_container_add(GTK_CONTAINER(lp->lp_box), scroll);
}
