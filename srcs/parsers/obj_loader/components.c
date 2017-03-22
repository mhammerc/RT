#include "obj_parser.h"

int			count_components_line(char **line, ssize_t ret,
		t_faces_components *components)
{
	char	**split;

	(*line)[ret - 1] = 0;
	split = ft_strsplit(*line, ' ');
	if (!split)
		return (0);
	if ((split[0] && split[0][0] == '#') || !split[0])
	{
		free(*line);
		*line = NULL;
		strsplit_free(split);
		return (2);
	}
	if (ft_strcmp(split[0], "v") == 0)
		++components->n_sommets;
	else if (ft_strcmp(split[0], "vt") == 0)
		++components->n_textures;
	else if (ft_strcmp(split[0], "vn") == 0)
		++components->n_normales;
	else if (ft_strcmp(split[0], "f") == 0)
		++components->n_faces;
	free(*line);
	*line = NULL;
	strsplit_free(split);
	return (1);
}

int			count_components(char *filename, t_faces_components *components)
{
	char	*line;
	FILE	*fp;
	ssize_t	ret;
	size_t	n;
	int		ret2;

	n = 0;
	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		ret2 = count_components_line(&line, ret, components);
		if (ret2 == 0)
			return (0);
		if (ret2 == 2)
			continue ;
	}
	fclose(fp);
	return (1);
}

void		prepare_components(t_faces_components *components)
{
	components->sommets = (t_vec3*)malloc(sizeof(t_vec3)
			* components->n_sommets);
	components->textures = (t_vec2*)malloc(sizeof(t_vec2)
			* components->n_textures);
	components->normales = (t_vec3*)malloc(sizeof(t_vec3)
			* components->n_normales);
	components->n_sommets = 0;
	components->n_textures = 0;
	components->n_normales = 0;
}

void		free_components(t_faces_components *components)
{
	free(components->sommets);
	free(components->textures);
	free(components->normales);
}
