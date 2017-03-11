#include "ui.h"

void	ft_fill_camera_position(t_env *env, char **tab)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	env->camera.pos.x = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	env->camera.pos.y = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	env->camera.pos.z = atof(tmp2);
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
	env->camera.dir.x = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	env->camera.dir.y = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	env->camera.dir.z = atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->camera_filled[1] = 1;
}
