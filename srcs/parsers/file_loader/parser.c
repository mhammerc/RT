#include "ui.h"

static void		ft_parse_line(t_env *env)
{
	if (ft_strncmp(env->ln, "camera:", 7) == 0)
		p_parse_camera(env);
	else if (ft_strncmp(env->ln, "object:", 7) == 0)
		p_parse_object(env);
}

void			ft_read_file(char *name, t_env *env)
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
			ft_parse_line(env);
	}
	free(env->ln);
}
