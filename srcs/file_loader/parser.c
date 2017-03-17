#include "ui.h"

size_t		count_tab(char *ln)
{
	size_t	i;

	i = 0;
	while (ln[i] && ln[i] == '\t')
		++i;
	return (i);
}

void	p_parse_camera(t_env *env, char *ln)
{
	int		ret;
	char	*ln2;

	ft_bzero(&env->camera, sizeof(t_parser_cam));
	while ((ret = ft_get_next_line(env->fd, &env->ln)))
	{
		if (ret == -1)
		{
			ft_puterr(ERR_FILE_OPEN, env);
		}
		ln2 = ft_strtrim(env->ln);
		if (ft_strncmp(ln2, "position:", 9) == 0)
			env->camera.pos = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "lookAt:", 7) == 0)
			env->camera.look_at = p_read_vec3(env, ln2);
		else if (*ln2 == 0)
			break ;
		free(ln2);
	}
}

static enum e_object_type	p_str_to_type(char *str)
{
	if (ft_strncmp(str, "SPHERE", 6) == 0)
		return (SPHERE);
	else if (ft_strncmp(str, "PLANE", 5) == 0)
		return (PLANE);
	else if (ft_strncmp(str, "CONE", 4) == 0)
		return (CONE);
	else if (ft_strncmp(str, "CYLINDER", 8) == 0)
		return (CYLINDER);
	else if (ft_strncmp(str, "TORUS", 5) == 0)
		return (TORUS);
	else if (ft_strncmp(str, "CSG", 3) == 0)
		return (CSG);
	else if (ft_strncmp(str, "POLYGONS", 8) == 0)
		return (POLYGONS);
	else if (ft_strncmp(str, "EMPTY", 5) == 0)
		return (EMPTY);
	else if (ft_strncmp(str, "LIGHT", 5) == 0)
		return (LIGHT);
	return (EMPTY);
}

void	p_parse_object(t_env *env, char *ln)
{
	int			ret;
	char		*ln2;
	t_object	new_object;

	ft_bzero(&new_object, sizeof(t_object));
	new_object.kspec = 1.;
	new_object.kdiff = 1.;
	while ((ret = ft_get_next_line(env->fd, &env->ln)))
	{
		if (ret == -1)
		{
			ft_puterr(ERR_FILE_OPEN, env);
		}
		ln2 = ft_strtrim(env->ln);
		if (ft_strncmp(ln2, "type:", 5) == 0)
			new_object.type = p_str_to_type(ln2 + 6); //TODO trim
		else if (ft_strncmp(ln2, "position:", 9) == 0)
			new_object.pos = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "rotation:", 9) == 0)
			new_object.rot = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "radius:", 7) == 0)
			new_object.radius = atof(ln2 + 7);
		else if (ft_strncmp(ln2, "length:", 7) == 0)
			new_object.length = atof(ln2 + 7);
		else if (ft_strncmp(ln2, "color:", 6) == 0)
			new_object.color = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "name:", 5) == 0)
		{
			new_object.name[0] = 0;
			//TODO trim
			ft_strlcat(new_object.name, ln2 + 5, 80);
		}
		else if (ft_strncmp(ln2, "kdiff:", 6) == 0)
			new_object.kdiff = atof(ln2 + 6);
		else if (ft_strncmp(ln2, "kspec:", 6) == 0)
			new_object.kspec = atof(ln2 + 6);
		else if (ft_strncmp(ln2, "csgOperation:", 13) == 0)
			new_object.operation = ln2[14]; //TODO trim
		else if (ft_strncmp(ln2, "object:", 7) == 0)
		{
			size_t tabs = count_tab(env->ln);
			if (tabs == env->depth)
			{
				free(ln2);
				ft_lstadd(env->current_object, ft_lstnew(&new_object, sizeof(t_object)));
				env->current_object = &(*env->current_object)->next;
				p_parse_object(env, env->ln);
				return ;
			}
			else if (tabs > env->depth)
			{
				size_t old_depth = env->depth;
				env->depth = tabs;
				t_list	**old;
				ft_lstadd(env->current_object, ft_lstnew(&new_object, sizeof(t_object)));
				old = env->current_object;
				env->current_object = &(*env->current_object)->children;
				p_parse_object(env, env->ln);
				env->current_object = old;
				env->depth = old_depth;
				tabs = count_tab(env->ln);
				if (tabs < env->depth)
					return ;
			}
			else if (tabs < env->depth)
			{
				free(ln2);
				ft_lstadd(env->current_object, ft_lstnew(&new_object, sizeof(t_object)));
				return ;
			}
		}
		free(ln2);
	}
	ft_lstadd(env->current_object, ft_lstnew(&new_object, sizeof(t_object)));
}

void	ft_parse_line(t_env *env, char *ln)
{
	if (ft_strncmp(env->ln, "camera:", 7) == 0)
		p_parse_camera(env, env->ln);
	else if (ft_strncmp(env->ln, "object:", 7) == 0)
		p_parse_object(env, env->ln);
}

void	ft_read_file(char *name, t_env *env)
{
	int		fd;
	int		ret;
	char	*ln;

	ln = NULL;
	env->current_object = &env->objects;
	fd = open(name, O_RDONLY);
	if (fd == -1 || read(fd, 0, 0) == -1)
	{
		ft_puterr(ERR_FILE_OPEN, env);
		return ;
	}
	env->fd = fd;
	while ((ret = ft_get_next_line(fd, &env->ln)))
	{
		if (ret == -1)
			ft_puterr(ERR_FILE_OPEN, env);
		if (ft_strcmp(env->ln, "") != 0 && *env->ln != '#')
			ft_parse_line(env, env->ln);
	}
}
