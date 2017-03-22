/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:05:09 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:37:40 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Add the object `object` to the scene.
** This function may be called from outside.
** This is why it use get_interface().
*/

void		add_object(t_object object, gboolean render_new)
{
	t_ui		*ui;
	t_list		*lst;
	GtkTreeIter	elem;
	GtkTreeIter *father;

	ui = get_interface();
	if (!ui->selected_obj.object)
	{
		ft_lstpushback(&ui->objs, ft_lstnew(&object, sizeof(t_object)));
		if (render_new)
			refresh_obj_tree(ui);
	}
	else
	{
		father = &ui->selected_obj.iter;
		lst = ft_lstat_child(ui->objs, ui->selected_obj.index,
			ui->selected_obj.depth);
		ft_lstpushback(&lst->children, ft_lstnew(&object, sizeof(t_object)));
		gtk_tree_store_append(ui->lp->tree.store, &elem, father);
		gtk_tree_store_set(ui->lp->tree.store, &elem, 0, object.name, 1,
			get_el_type_char(&object), -1);
		gtk_tree_view_expand_row(GTK_TREE_VIEW(ui->lp->tree.tree),
			gtk_tree_model_get_path(GTK_TREE_MODEL(ui->lp->tree.store), father),
			FALSE);
	}
}
