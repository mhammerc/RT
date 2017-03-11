#include "ui.h"

void	ft_fill_scene_size(t_env *env, char **tab)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	env->scene.size.x = ft_atoi(tmp2) > 1920 ? 1920 : ft_atoi(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	env->scene.size.y = ft_atoi(tmp2) > 1080 ? 1080 : ft_atoi(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->scene_filled[0] = 1;
}

void	ft_fill_scene_name(t_env *env, char **tab)
{
	char	*tmp;

	tmp = ft_strtrim(tab[1]);
	env->scene.name = tmp;
	env->scene_filled[1] = 1;
}
