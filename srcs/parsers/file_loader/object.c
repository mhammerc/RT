#include <ui.h>
#include <file_loader.h>

static int		read_properties3(char *ln2, t_object *new_object, t_env *env,
		size_t tabs)
{
	if (ft_strncmp(ln2, "object:", 7) == 0)
	{
		tabs = count_tab(env->ln);
		if (tabs == env->depth)
		{
			free(ln2);
			ft_lstadd(env->current_object, ft_lstnew(new_object,
						sizeof(t_object)));
			env->current_object = &(*env->current_object)->next;
			p_parse_object(env);
			return (0);
		}
		else if (tabs > env->depth)
		{
			if (!deeper_object(ln2, new_object, env, &tabs))
				return (0);
		}
		else if (tabs < env->depth)
		{
			less_deeper_object(ln2, new_object, env);
			return (0);
		}
	}
	return (1);
}

void			p_parse_object(t_env *env)
{
	int			ret;
	char		*ln2;
	t_object	new_object;

	ft_bzero(&new_object, sizeof(t_object));
	new_object.kspec = 1.;
	new_object.kdiff = 1.;
	new_object.operation = '0';
	free(env->ln);
	while ((ret = ft_get_next_line(env->fd, &env->ln)))
	{
		if (ret == -1)
		{
			ft_puterr(ERR_FILE_OPEN, env);
		}
		ln2 = ft_strtrim(env->ln);
		read_properties1(ln2, &new_object);
		read_properties2(ln2, &new_object);
		if (!read_properties3(ln2, &new_object, env, 0))
			return ;
		read_properties4(ln2, &new_object);
		free(ln2);
	}
	ft_lstadd(env->current_object, ft_lstnew(&new_object, sizeof(t_object)));
}
