/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:03:27 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:24:52 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** refresh left panel (obj_tree)
*/

static void		refresh_obj_tree_aux(t_ui *ui, t_list *objects,
															GtkTreeIter *father)
{
	GtkTreeIter	elem;
	t_object	*object;

	object = objects->content;
	gtk_tree_store_append(ui->lp->tree.store, &elem, father);
	gtk_tree_store_set(ui->lp->tree.store, &elem, 0, object->name, 1,
		get_el_type_char(object), -1);
	if (objects->next)
		refresh_obj_tree_aux(ui, objects->next, father);
	if (objects->children)
		refresh_obj_tree_aux(ui, objects->children, &elem);
}

void			refresh_obj_tree(t_ui *ui)
{
	gtk_tree_store_clear(ui->lp->tree.store);
	if (ui->objs)
		refresh_obj_tree_aux(ui, ui->objs, NULL);
	ui->selected_obj.object = NULL;
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

void			free_obj_tree(t_ui *ui)
{
	t_list		*to_del;

	ui->selected_obj.object = NULL;
	while (ui->objs)
	{
		to_del = ui->objs;
		ui->objs = ui->objs->next;
		free(to_del);
	}
	ui->objs = NULL;
}
