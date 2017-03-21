#include <file_loader.h>

void	p_parse_camera(t_env *env, char *ln)
{
	int		ret;
	char	*ln2;

	ft_bzero(&env->camera, sizeof(t_parser_cam));
	free(env->ln);
	env->camera.pos = (t_vec3){0., 0., 7.};
	env->camera.up = (t_vec3){0., 1., 0.};
	while ((ret = ft_get_next_line(env->fd, &env->ln)))
	{
		if (ret == -1)
		{
			ft_puterr(ERR_FILE_OPEN, env);
			break ;
		}
		ln2 = ft_strtrim(env->ln);
		if (ft_strncmp(ln2, "position:", 9) == 0)
			env->camera.pos = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "lookAt:", 7) == 0)
			env->camera.look_at = p_read_vec3(env, ln2);
		else if (ft_strncmp(ln2, "up:", 3) == 0)
			env->camera.up = p_read_vec3(env, ln2);
		if (*ln2 == 0)
		{
			free(ln2);
			free(env->ln);
			break ;
		}
		free(ln2);
		free(env->ln);
	}
}
