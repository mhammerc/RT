/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_el_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:32:20 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 22:35:09 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		element_edited()
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

void		edit_element_properties(GtkTreeView *tree_view,
					GtkTreePath *path, GtkTreeViewColumn *column, gpointer data)
{
	t_ui				*ui;
	t_list				*obj_lst;
	int					*tmp;

	ui = (t_ui*)data;
	(void)tree_view;
	(void)column;
	tmp = gtk_tree_path_get_indices_with_depth(path, &(ui->selected_obj.depth));
	ft_memcpy(ui->selected_obj.index, tmp , 4 * (ui->selected_obj.depth));
	obj_lst = ft_lstat_child(ui->objs, ui->selected_obj.index,
														ui->selected_obj.depth);
	ui->selected_obj.object = (t_object*)obj_lst->content;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(ui->lp->tree.store),
												&ui->selected_obj.iter, path);
	clear_properties_list(ui);
	gtk_container_add(GTK_CONTAINER(ui->rp->el_prop_lst),
							gtk_label_new_with_mnemonic("_Element Properties"));
	add_shared_widgets(ui, ui->selected_obj.object, ui->rp->el_prop_lst);
	add_situational_widgets(ui, ui->selected_obj.object, ui->rp->el_prop_lst);
	gtk_widget_show_all(ui->window);
}

void		clear_properties_list(t_ui *ui)
{
	GList	*children;
	GList	*iter;

	children = gtk_container_get_children(GTK_CONTAINER(ui->rp->el_prop_lst));
	iter = children;
	while (iter != NULL)
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));
		iter = g_list_next(iter);
	}
	g_list_free(children);
	ui->rp->el_prop.length = NULL;
	ui->rp->el_prop.radius = NULL;
}
