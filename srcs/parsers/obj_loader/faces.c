#include "obj_parser.h"

void		init_faces(t_object *object, t_faces_components *components)
{
	object->faces = (t_face*)malloc(sizeof(t_face) * components->n_faces);
	object->nb_faces = components->n_faces;
	ft_bzero(object->faces, sizeof(t_face) * components->n_faces);
	components->n_faces = 0;
}

int			copy_one_face2(t_face *face, t_faces_components *components,
		char **split)
{
	t_vec3	tmp;
	size_t	i;

	i = 1;
	while (i <= face->nb)
	{
		if ((size_t)atoi(split[i]) > components->n_sommets
	|| (size_t)atoi(ft_strrchr(split[i], '/') + 1) > components->n_normales)
			return (0);
		tmp = components->sommets[atoi(split[i]) - 1];
		face->sommets[i - 1] = tmp;
		face->normales[i - 1] =
			components->normales[atoi(ft_strrchr(split[i], '/') + 1) - 1];
		++i;
	}
	return (1);
}

int			copy_one_face(t_object *object, t_faces_components *components,
		char **split)
{
	t_face	face;
	size_t	n;

	if (split[0] && ft_strcmp(split[0], "f") == 0)
	{
		n = 0;
		while (split[n])
			++n;
		face.nb = n - 1;
		face.sommets = (t_vec3*)malloc(sizeof(t_vec3) * face.nb);
		face.normales = (t_vec3*)malloc(sizeof(t_vec3) * face.nb);
		face.textures = (t_vec2*)malloc(sizeof(t_vec2) * face.nb);
		if (!face.sommets || !face.normales || !face.textures)
			return (0);
		if (!copy_one_face2(&face, components, split))
			return (0);
		object->faces[components->n_faces] = face;
		++components->n_faces;
	}
	return (1);
}

int			copy_faces(t_object *object, char *filename,
		t_faces_components *components)
{
	char	*line;
	char	**split;
	FILE	*fp;
	ssize_t	ret;
	size_t	n;

	init_faces(object, components);
	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		line[ret - 1] = 0;
		split = ft_strsplit(line, ' ');
		if (!copy_one_face(object, components, split))
			return (0);
		strsplit_free(split);
	}
	free_components(components);
	return (1);
}
