/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 01:48:29 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 18:08:07 by gpoblon          ###   ########.fr       */
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
	hook_up_obj_lst(env->entity_lst, ui->objs);
	g_assert_no_error (error);
}

void			hook_up_obj_lst(t_entity_lst *lst, t_list *objs)
{
	t_object	*cur_obj;

	while (lst)
	{
		cur_obj = ((t_object*)ui->objs->content);
		cur_obj->type = lst->entity.type;
		cur_obj->name = ft_strdup(lst->entity.obj.name);
		cur_obj->pos = lst->entity.obj.pos;
		cur_obj->rot = lst->entity.obj.rot;
		cur_obj->length = lst->entity.obj.length;
		cur_obj->radius = lst->entity.obj.radius;
		cur_obj->color = lst->entity.obj.color;
		ft_lstpushback(&objs, ft_lstnew(&cur_obj, sizeof(t_object)));
		lst = lst->next;
		objs = objs->next;
	}
}

// int			main(int argc, char *argv[])
// {
// 	t_env			env;
// 	t_entity_lst	*tmp;
// 	t_group_lst		*tmp2;
//
// 	env.line_count = 0;
// 	env.entity_lst = NULL;
// 	env.group_lst = NULL;
// 	env.group_tmp = NULL;
// 	tmp = NULL;
// 	tmp2 = NULL;
// 	ft_init_tabs(&env);
// 	ft_read_file(argv[1], &env);
// 	if (argc != 2)
// 	{
// 		ft_puterr(ERR_WRONG_ARGS, &env);
// 		return (-1);
// 	}
// 	if (ft_check_all(&env))
// 	{
// 		if (!env.entity_lst)
// 			ft_puterr(ERR_NO_ENTITY, &env);
// 		else
// 		{
// 			printf("scene size : %d; %d\n", env.scene.size.x, env.scene.size.y);
// 			printf("scene name : %s\n\n", env.scene.name);
// 			printf("camera position : %f; %f; %f\n", env.camera.position.x, env.camera.position.y, env.camera.position.z);
// 			printf("camera rotation : %f; %f; %f\n\n", env.camera.rotation.x, env.camera.rotation.y, env.camera.rotation.z);
// 			if (env.group_tmp)
// 			{
// 				ft_push_group(&env.group_lst, ft_new_group(env.group_tmp));
// 			}
// 			/*
// 			tmp = env.entity_lst;
// 			while (tmp)
// 			{
// 				if (tmp->entity.type == OBJECT)
// 				{
// 					printf("object position : %f; %f; %f\n", tmp->entity.obj.position.x, tmp->entity.obj.position.y, tmp->entity.obj.position.z);
// 					printf("object rotation : %f; %f; %f\n", tmp->entity.obj.rotation.x, tmp->entity.obj.rotation.y, tmp->entity.obj.rotation.z);
// 					printf("object radius : %f\n", tmp->entity.obj.radius);
// 					printf("object length : %f\n", tmp->entity.obj.length);
// 					printf("object name : %s\n\n", tmp->entity.obj.name);
// 				}
// 				else
// 				{
// 					printf("light position : %f; %f; %f\n", tmp->entity.light.position.x, tmp->entity.light.position.y,
// 						tmp->entity.light.position.z);
// 					printf("light intensity : %f\n", tmp->entity.light.intensity);
// 					printf("light color : %d\n\n", tmp->entity.light.color);
// 				}
// 				tmp = tmp->next;
// 			}
// 			*/
// 			tmp2 = env.group_lst;
// 			while (tmp2)
// 			{
// 				tmp = tmp2->group;
// 				printf("=============================\n");
// 				while (tmp)
// 				{
// 					if (tmp->entity.type == OBJECT)
// 					{
// 						printf("object position : %f; %f; %f\n", tmp->entity.obj.position.x, tmp->entity.obj.position.y,
// 							tmp->entity.obj.position.z);
// 						printf("object rotation : %f; %f; %f\n", tmp->entity.obj.rotation.x, tmp->entity.obj.rotation.y,
// 							tmp->entity.obj.rotation.z);
// 						printf("object radius : %f\n", tmp->entity.obj.radius);
// 						printf("object length : %f\n", tmp->entity.obj.length);
// 						printf("object name : %s\n\n", tmp->entity.obj.name);
// 					}
// 					else
// 					{
// 						printf("light position : %f; %f; %f\n", tmp->entity.light.position.x, tmp->entity.light.position.y,
// 							tmp->entity.light.position.z);
// 						printf("light intensity : %f\n", tmp->entity.light.intensity);
// 						printf("light color : %d\n\n", tmp->entity.light.color);
// 					}
// 						tmp = tmp->next;
// 				}
// 				tmp2 = tmp2->next;
// 			}
// 		}
// 	}
// 	else
// 		ft_puterr(ERR_FILE_SYNTAX, &env);
// 	sleep(10000);
// 	return (0);
// }
