/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:16:46 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 17:45:34 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_fill_object_type(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	if (!ft_strcmp(tmp, "PLANE"))
		entity->obj.type = PLANE;
	else if (!ft_strcmp(tmp, "SPHERE"))
		entity->obj.type = SPHERE;
	else if (!ft_strcmp(tmp, "CYLINDER"))
		entity->obj.type = CYLINDER;
	else if (!ft_strcmp(tmp, "CONE"))
		entity->obj.type = CONE;
	else if (!ft_strcmp(tmp, "LIGHT"))
		entity->obj.type = LIGHT;
	else if (!ft_strcmp(tmp, "EMPTY"))
		entity->obj.type = EMPTY;
	else
		ft_puterr(ERR_UNKNOWN_OBJ, env);
	env->object_filled[0] = 1;
	free(tmp);
}

void	ft_fill_object_position(t_env *env, char **tab, t_entity *entity)
{
	char	**tmp;
	char	*tmp2;

	entity->type = OBJECT;
	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	entity->obj.pos.x = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	entity->obj.pos.y = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	entity->obj.pos.z = ft_atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->object_filled[1] = 1;
}

void	ft_fill_object_rotation(t_env *env, char **tab, t_entity *entity)
{
	char	**tmp;
	char	*tmp2;

	entity->type = OBJECT;
	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	entity->obj.rot.x = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	entity->obj.rot.y = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	entity->obj.rot.z = ft_atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->object_filled[2] = 1;
}

void	ft_fill_object_radius(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	entity->obj.radius = ft_atof(tmp);
	free(tmp);
	env->object_filled[3] = 1;
}

void	ft_fill_object_length(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	entity->obj.length = ft_atof(tmp);
	free(tmp);
	env->object_filled[4] = 1;
}

void	ft_fill_object_name(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	if (ft_strlen(tmp) > 80)
		ft_puterr(ERR_FILE_SYNTAX, env);
	ft_strcpy(entity->obj.name, tmp);
	free(tmp);
	env->object_filled[5] = 1;
}
