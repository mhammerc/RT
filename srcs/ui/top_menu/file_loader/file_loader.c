/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 01:48:29 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 18:22:45 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ui.h"

void			load_file(char *filename)
{
	t_ui			*ui;
	t_env			env;

	ui = get_interface();
	env.line_count = 0;
	env.entity_lst = NULL;
	env.group_lst = NULL;
	env.group_tmp = NULL;
	ft_init_tabs(&env);
	ft_read_file(filename, &env);
	hook_up_obj_lst(env.entity_lst, ui->objs);
	// g_assert_no_error (error);
}

void			hook_up_obj_lst(t_entity_lst *lst, t_list *objs)
{
	t_object	*cur_obj;

	while (lst)
	{
		cur_obj = ((t_object*)objs->content);
		cur_obj->type = lst->entity.type;
		ft_strcpy(cur_obj->name, lst->entity.name);
		cur_obj->pos = lst->entity.pos;
		cur_obj->rot = lst->entity.rot;
		cur_obj->length = lst->entity.length;
		cur_obj->radius = lst->entity.radius;
		cur_obj->color = lst->entity.color;
		ft_lstpushback(&objs, ft_lstnew(&cur_obj, sizeof(t_object)));
		lst = lst->next;
		objs = objs->next;
	}
}
