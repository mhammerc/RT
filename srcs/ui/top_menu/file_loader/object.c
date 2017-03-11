#include "ui.h"

void	ft_fill_object_type(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->env_type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	if (!ft_strcmp(tmp, "PLANE"))
		entity->type = PLANE;
	else if (!ft_strcmp(tmp, "SPHERE"))
		entity->type = SPHERE;
	else if (!ft_strcmp(tmp, "CYLINDER"))
		entity->type = CYLINDER;
	else if (!ft_strcmp(tmp, "CONE"))
		entity->type = CONE;
	else if (!ft_strcmp(tmp, "LIGHT"))
		entity->type = LIGHT;
	else if (!ft_strcmp(tmp, "EMPTY"))
		entity->type = EMPTY;
	else
		ft_puterr(ERR_UNKNOWN_OBJ, env);
	env->object_filled[0] = 1;
	free(tmp);
}

void	ft_fill_object_position(t_env *env, char **tab, t_entity *entity)
{
	char	**tmp;
	char	*tmp2;

	entity->env_type = OBJECT;
	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	entity->pos.x = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	entity->pos.y = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	entity->pos.z = atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->object_filled[1] = 1;
}

void	ft_fill_object_rotation(t_env *env, char **tab, t_entity *entity)
{
	char	**tmp;
	char	*tmp2;

	entity->env_type = OBJECT;
	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	entity->rot.x = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	entity->rot.y = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	entity->rot.z = atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->object_filled[2] = 1;
}

void	ft_fill_object_radius(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->env_type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	entity->radius = atof(tmp);
	free(tmp);
	env->object_filled[3] = 1;
}

void	ft_fill_object_length(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->env_type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	entity->length = atof(tmp);
	free(tmp);
	env->object_filled[4] = 1;
}

void	ft_fill_object_name(t_env *env, char **tab, t_entity *entity)
{
	char	*tmp;

	entity->env_type = OBJECT;
	tmp = ft_strtrim(tab[1]);
	if (ft_strlen(tmp) > 80)
		ft_puterr(ERR_FILE_SYNTAX, env);
	ft_strcpy(entity->name, tmp);
	free(tmp);
	env->object_filled[5] = 1;
}

void	ft_fill_object_color(t_env *env, char **tab, t_entity *entity)
{
	char	**tmp;
	char	*tmp2;

	entity->env_type = OBJECT;
	tmp = ft_strsplit(tab[1], ';');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		ft_puterr(ERR_FILE_SYNTAX, env);
	tmp2 = ft_strtrim(tmp[0]);
	entity->color.x = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[1]);
	entity->color.y = atof(tmp2);
	free(tmp2);
	tmp2 = ft_strtrim(tmp[2]);
	entity->color.z = atof(tmp2);
	free(tmp2);
	ft_free_split(tmp);
	env->object_filled[1] = 1;
}
