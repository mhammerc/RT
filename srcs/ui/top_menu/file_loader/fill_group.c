#include "ui.h"

void	ft_fill_object_group(t_env *env, char *ln)
{
	static t_entity	entity;
	char			**tmp;
	char			*tmp2;

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
	else if (!ft_strcmp(tmp2, "kspec"))
		ft_fill_object_kspec(env, tmp, &entity);
		else if (!ft_strcmp(tmp2, "kdiff"))
		ft_fill_object_kdiff(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "color"))
		ft_fill_object_color(env, tmp, &entity);
	else if (!ft_strcmp(tmp2, "name"))
		ft_fill_object_name(env, tmp, &entity);
	else
		ft_puterr(ERR_FILE_SYNTAX, env);
	if (ft_check_entity(env, OBJECT))
	{
		ft_push_entity(&env->entity_lst, ft_new_entity(entity));
		ft_push_entity(&env->group_tmp, ft_new_entity(entity));
		ft_reset(env, OBJECT);
		if (env->entity_type != GROUP)
			env->entity_type = UNDEFINED;
		env->group_entity_type = UNDEFINED;
	}
	free(tmp2);
	ft_free_split(tmp);
}
