#include "ui.h"

int		ft_count_tabs(const char *s)
{
	int	count;

	count = -1;
	while (s[++count] == '\t')
		continue ;
	return (count);
}

void	ft_get_entity(t_env *env, char *s)
{
	char	*tmp;

	tmp = ft_strtrim(s);
	if (!ft_strcmp(tmp, "scene"))
		env->entity_type = SCENE;
	else if (!ft_strcmp(tmp, "camera"))
		env->entity_type = CAMERA;
	else if (!ft_strcmp(tmp, "object"))
		env->entity_type = OBJECT;
	else if (!ft_strcmp(tmp, "group"))
		env->entity_type = GROUP;
	else
		ft_puterr(ERR_FILE_SYNTAX, env);
	free(tmp);
}

void	ft_get_group_entity(t_env *env, char *s)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_strsplit(s, ':');
	tmp2 = ft_strtrim(tmp[0]);
	if (!ft_strcmp(tmp2, "object"))
		env->group_entity_type = OBJECT;
	else
		ft_puterr(ERR_FILE_SYNTAX, env);
	ft_free_split(tmp);
	free(tmp2);
}

void	ft_parse_line(t_env *env, char *ln)
{
	char			**tmp;
	t_entity_lst	*tmp_lst;

	tmp = NULL;
	if (!ft_count_tabs(ln))
	{
		if (env->entity_type == GROUP)
		{
			tmp_lst = ft_cpy_lst(env->group_tmp);
			ft_push_group(&env->group_lst, ft_new_group(tmp_lst));
			ft_free_list(&env->group_tmp);
		}
		tmp = ft_strsplit(ln, ':');
		ft_get_entity(env, tmp[0]);
		ft_free_split(tmp);
	}
	else if (ft_count_tabs(ln) == 1)
	{
		if (env->entity_type == GROUP && env->group_entity_type == UNDEFINED)
			ft_get_group_entity(env, ln);
		else if (env->entity_type != GROUP)
			ft_fill_env(env, ln);
		else
			ft_puterr(ERR_FILE_SYNTAX, env);
	}
	else if (ft_count_tabs(ln) == 2)
	{
		if (env->entity_type != GROUP || env->group_entity_type == UNDEFINED)
			ft_puterr(ERR_FILE_SYNTAX, env);
		ft_fill_group(env, ln);
	}
}

void	ft_read_file(char *name, t_env *env)
{
	int		fd;
	int		ret;
	char	*ln;

	ln = NULL;
	fd = open(name, O_RDONLY);
	while ((ret = ft_get_next_line(fd, &ln)))
	{
		env->line_count++;
		if (ret == -1)
			ft_puterr(ERR_FILE_OPEN, env);
		if (ft_strcmp(ln, ""))
			ft_parse_line(env, ln);
		free(ln);
	}
	free(ln);
}
