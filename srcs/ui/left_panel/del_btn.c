/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_btn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:01:22 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/22 17:51:46 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	ui_free_object(t_object *object)
{
	size_t	i;

	if (object->filename)
		g_free(object->filename);
	if (object->texture_filename)
		g_free(object->texture_filename);
	free_texture(&object->texture);
	if (object->faces)
	{
		i = 0;
		while (i < object->nb_faces)
		{
			free(object->faces[i].sommets);
			free(object->faces[i].normales);
			free(object->faces[i].textures);
			++i;
		}
		free(object->faces);
	}
	free(object);
}

/*
** Don't free next because we want to free that specific node
*/

static void	ui_free_list_object(t_list *objects)
{
	t_object	*object;

	object = objects->content;
	ui_free_object(object);
	if (objects->children)
		ui_free_list_object(objects->children);
	free(objects);
}

static void	del_selected_obj(t_ui *ui, t_list *tmp, t_list *tmp_clean)
{
	if (ui->selected_obj.index[ui->selected_obj.depth - 1] == 0)
	{
		if (ui->selected_obj.depth == 1)
		{
			tmp_clean = ui->objs;
			ui->objs = ui->objs->next;
			ui_free_list_object(tmp_clean);
		}
		else
		{
			tmp = ft_lstat_child(ui->objs, ui->selected_obj.index,
													ui->selected_obj.depth - 1);
			tmp_clean = tmp->children;
			tmp->children = tmp_clean->next;
			ui_free_list_object(tmp_clean);
		}
	}
	else
	{
		tmp = ft_lstat_child_before(ui->objs, ui->selected_obj.index,
														ui->selected_obj.depth);
		tmp_clean = tmp->next;
		tmp->next = tmp_clean->next;
		ui_free_list_object(tmp_clean);
	}
}

void		del_obj_btn(GtkButton *button, gpointer data)
{
	t_list			*tmp;
	t_list			*tmp_clean;
	t_ui			*ui;

	ui = (t_ui*)data;
	tmp = NULL;
	tmp_clean = NULL;
	(void)button;
	if (ui->selected_obj.object)
	{
		del_selected_obj(ui, tmp, tmp_clean);
		refresh_obj_tree(ui);
		clear_properties_list(ui);
	}
}
