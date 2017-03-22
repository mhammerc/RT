#include <ui.h>
#include <file_loader.h>

void		read_properties1(char *ln2, t_object *new_object)
{
	char	*ln3;

	if (ft_strncmp(ln2, "position:", 9) == 0)
		new_object->pos = p_read_vec3(ln2);
	else if (ft_strncmp(ln2, "rotation:", 9) == 0)
		new_object->rot = p_read_vec3(ln2);
	else if (ft_strncmp(ln2, "radius:", 7) == 0)
		new_object->radius = atof(ln2 + 7);
	else if (ft_strncmp(ln2, "length:", 7) == 0)
		new_object->length = atof(ln2 + 7);
	else if (ft_strncmp(ln2, "color:", 6) == 0)
		new_object->color = p_read_vec3(ln2);
	else if (ft_strncmp(ln2, "name:", 5) == 0)
	{
		new_object->name[0] = 0;
		ln3 = ft_strtrim(ln2 + 5);
		ft_strlcat(new_object->name, ln3, 80);
		free(ln3);
	}
	else if (ft_strncmp(ln2, "texture:", 8) == 0)
	{
		ln3 = ft_strtrim(ln2 + 8);
		new_object->have_texture = ft_atoi(ln3);
		free(ln3);
	}
}

void 	read_properties2(char *ln2, t_object *new_object)
{
	char	*ln3;

	if (ft_strncmp(ln2, "type:", 5) == 0)
	{
		ln3 = ft_strtrim(ln2 + 5);
		new_object->type = p_str_to_type(ln3);
		free(ln3);
	}
	else if (ft_strncmp(ln2, "csgOperation:", 13) == 0)
	{
		ln3 = ft_strtrim(ln2 + 13);
		new_object->operation = *ln3;
		free(ln3);
	}
	else if (ft_strncmp(ln2, "filename:", 9) == 0)
	{
		ln3 = ft_strtrim(ln2 + 9);
		new_object->filename = ft_strdup(ln3);
		free(ln3);
	}
	else if (ft_strncmp(ln2, "kdiff:", 6) == 0)
		new_object->kdiff = atof(ln2 + 6);
	else if (ft_strncmp(ln2, "kspec:", 6) == 0)
		new_object->kspec = atof(ln2 + 6);
}

int		deeper_object(char *ln2, t_object *new_object, t_env *env,
		size_t *tabs)
{
	size_t	old_depth;
	t_list	**old;

	old_depth = env->depth;
	env->depth = *tabs;
	ft_lstadd(env->current_object, ft_lstnew(new_object, sizeof(t_object)));
	old = env->current_object;
	env->current_object = &(*env->current_object)->children;
	p_parse_object(env);
	env->current_object = old;
	env->depth = old_depth;
	if (!env->ln)
		return (0);
	*tabs = count_tab(env->ln);
	if (*tabs < env->depth)
	{
		free(ln2);
		return (0);
	}
	return (1);
}

void		less_deeper_object(char *ln2, t_object *new_object, t_env *env)
{
	free(ln2);
	ft_lstadd(env->current_object, ft_lstnew(new_object, sizeof(t_object)));
}

void		read_properties4(char *ln2, t_object *new_object)
{
	char	*ln3;

	if (ft_strncmp(ln2, "texture_filename:", 17) == 0)
	{
		ln3 = ft_strtrim(ln2 + 17);
		new_object->texture_filename = ft_strdup(ln3);
		free(ln3);
	}
}
