/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 21:43:29 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 18:28:15 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	ft_fill_camera(t_env *env, char *ln)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(ln, ':');
	tmp2 = ft_strtrim(tmp[0]);
	if (!tmp[1])
		ft_puterr(ERR_FILE_SYNTAX, env);
	if (!ft_strcmp(tmp2, "position"))
		ft_fill_camera_position(env, tmp);
	else if (!ft_strcmp(tmp2, "direction"))
		ft_fill_camera_rotation(env, tmp);
	free(tmp2);
	ft_free_split(tmp);
}

void	ft_fill_object(t_env *env, char *ln)
{
	t_entity_lst	*entity_tmp;
	static t_entity	entity;
	char			**tmp;
	char			*tmp2;

	entity_tmp = NULL;
	tmp = ft_strsplit(ln, ':');
	tmp2 = ft_strtrim(tmp[0]);
	if (!tmp[1])
		ft_puterr(ERR_FILE_SYNTAX, env);
	if (!ft_strcmp(tmp2, "type"))
		ft_fill_object_type(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "position"))
		ft_fill_object_position(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "rotation"))
		ft_fill_object_rotation(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "radius"))
		ft_fill_object_radius(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "length"))
		ft_fill_object_length(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "name"))
		ft_fill_object_name(env, tmp, &entity);
	else
		ft_puterr(ERR_FILE_SYNTAX, env);
	if (ft_check_entity(env, OBJECT))
	{
		entity_tmp = ft_new_entity(entity);
		ft_push_entity(&env->entity_lst, entity_tmp);
		ft_reset(env, OBJECT);
		if (env->entity_type != GROUP)
			env->entity_type = UNDEFINED;
		env->group_entity_type = UNDEFINED;
	}
	free(tmp2);
	ft_free_split(tmp);
}

void	ft_fill_group(t_env *env, char *ln)
{
	if (env->group_entity_type == OBJECT)
		ft_fill_object_group(env, ln);
}

void	ft_fill_scene(t_env *env, char *ln)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(ln, ':');
	if (!tmp[1])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	if (!ft_strcmp(tmp2, "size"))
		ft_fill_scene_size(env, tmp);
	else if (!ft_strcmp(tmp2, "name"))
		ft_fill_scene_name(env, tmp);
	free(tmp2);
	ft_free_split(tmp);
}

void	ft_fill_env(t_env *env, char *ln)
{
	if (env->entity_type == SCENE)
		ft_fill_scene(env, ln);
	else if (env->entity_type == CAMERA)
		ft_fill_camera(env, ln);
	else if (env->entity_type == OBJECT)
		ft_fill_object(env, ln);
	else
		ft_puterr(ERR_FILE_SYNTAX, env);
}
