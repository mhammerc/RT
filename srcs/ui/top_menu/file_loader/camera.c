/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 20:29:18 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 18:28:02 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	ft_fill_camera_position(t_env *env, char **tab)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	env->camera.pos.x = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	env->camera.pos.y = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	env->camera.pos.z = ft_atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->camera_filled[0] = 1;
}

void	ft_fill_camera_rotation(t_env *env, char **tab)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	env->camera.dir.x = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	env->camera.dir.y = ft_atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	env->camera.dir.z = ft_atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->camera_filled[1] = 1;
}
