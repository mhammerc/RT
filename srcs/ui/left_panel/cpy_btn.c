/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_btn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:45:25 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 17:45:43 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		ft_lst_cpy(t_list **new, t_list *original)
{
	ft_lstpushback(new, ft_lstnew(original->content, sizeof(t_object)));
	if (original->children)
		ft_lst_cpy(&((*new)->children), original->children);
	if (original->next)
		ft_lst_cpy(&((*new)->next), original->next);
}

static void	cpy_obj_btn_aux(t_ui *ui, GtkTreePath *path, t_object *obj)
{
	refresh_obj_tree(ui);
	gtk_tree_view_expand_to_path(GTK_TREE_VIEW(ui->lp->tree.tree), path);
	gtk_tree_view_set_cursor(GTK_TREE_VIEW(ui->lp->tree.tree), path, 0, 0);
	ui->selected_obj.object = obj;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(ui->lp->tree.store),
		&ui->selected_obj.iter, path);
}

void		cpy_obj_btn(GtkButton *button, gpointer data)
{
	t_list			*tmp;
	t_list			*new;
	t_ui			*ui;
	GtkTreePath		*path;
	t_object		*obj;

	ui = (t_ui*)data;
	(void)button;
	new = NULL;
	if (ui->selected_obj.object)
	{
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(ui->lp->tree.store),
			&ui->selected_obj.iter);
		obj = ui->selected_obj.object;
		tmp = ft_lstat_child(ui->objs, ui->selected_obj.index,
														ui->selected_obj.depth);
		ft_lstpushback(&new, ft_lstnew(tmp->content, sizeof(t_object)));
		if (tmp->children)
			ft_lst_cpy(&new->children, tmp->children);
		ft_lstpushback(&tmp, new);
		cpy_obj_btn_aux(ui, path, obj);
	}
}
