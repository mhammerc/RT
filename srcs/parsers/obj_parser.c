#include "obj_parser.h"

/*
 * Attend d'etre teste avant la mise a la norme.
 * Revoir la securite du bouzin (si un malloc fail ou un truc)
 * a priori on prend pas les normales, mais on aura surement besoin des textures.
 * Aussi regarder si line doit etre free une fois sortie de la boucle de getline.
 */

static void free_strsplit(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
}

static int	start_parsing(t_object *object, char *filename)
{
	char				*line;
	char				**split;
	FILE				*fp;
	ssize_t				ret;
	size_t				n = 0;
	t_faces_components	components;
	t_vec3				tmp;
	t_vec2				tmp2;

	ft_bzero(&components, sizeof(t_faces_components));

	/* First, count elements. */
	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		line[ret - 1] = 0;
		split = ft_strsplit(line, ' ');
		if (!split)
			return (0);
		if ((split[0] && split[0][0] == '#') || !split[0])
		{
			free(line);
			line = NULL;
			free_strsplit(split);
			continue;
		}
		if (ft_strcmp(split[0], "v") == 0)
			++components.n_sommets;
		else if (ft_strcmp(split[0], "vt") == 0)
			++components.n_textures;
		else if (ft_strcmp(split[0], "vn") == 0)
			++components.n_normales;
		else if (ft_strcmp(split[0], "f") == 0)
			++components.n_faces;
		free(line);
		line = NULL;
		free_strsplit(split);
	}
	fclose(fp);

	/* Then, malloc and copy them. */
	components.sommets = (t_vec3*)malloc(sizeof(t_vec3) * components.n_sommets);
	components.textures = (t_vec2*)malloc(sizeof(t_vec2) * components.n_textures);
	components.normales = (t_vec3*)malloc(sizeof(t_vec3) * components.n_normales);
	if (!components.normales || !components.textures || !components.sommets)
		return (0);
	components.n_sommets = 0;
	components.n_textures = 0;
	components.n_normales = 0;

	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		line[ret - 1] = 0;
		split = ft_strsplit(line, ' ');
		if ((split[0] && split[0][0] == '#') || !split[0])
		{
			free(line);
			line = NULL;
			free_strsplit(split);
			continue;
		}
		if (ft_strcmp(split[0], "v") == 0)
		{
			if (!split[1] || !split[2] || !split[3])
				return (0);
			tmp.x = atof(split[1]);
			tmp.y = atof(split[2]);
			tmp.z = atof(split[3]);
			if (object->radius < tmp.x)
				object->radius = tmp.x;
			if (object->radius < tmp.y)
				object->radius = tmp.y;
			if (object->radius < tmp.z)
				object->radius = tmp.z;
			components.sommets[components.n_sommets++] = tmp;
		}
		else if (ft_strcmp(split[0], "vt") == 0)
		{
			if (!split[1] || !split[2])
				return (0);
			tmp2.x = atof(split[1]);
			tmp2.y = atof(split[2]);
			components.textures[components.n_textures++] = tmp2;
		}
		else if (ft_strcmp(split[0], "vn") == 0)
		{
			if (!split[1] || !split[2] || !split[3])
				return (0);
			tmp.x = atof(split[1]);
			tmp.y = atof(split[2]);
			tmp.z = atof(split[3]);
			components.normales[components.n_normales++] = tmp;
		}
		free(line);
		line = NULL;
		free_strsplit(split);
	}
	fclose(fp);

	/* Last pass: we can create faces. */
	t_face	face;
	object->faces = (t_face*)malloc(sizeof(t_face) * components.n_faces);
	if (!object->faces)
		return (0);
	object->nb_faces = components.n_faces;
	ft_bzero(object->faces, sizeof(t_face) * components.n_faces);
	components.n_faces = 0;
	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		line[ret - 1] = 0;
		split = ft_strsplit(line, ' ');
		int n = 0;
		size_t	i;
		if (split[0] && ft_strcmp(split[0], "f") == 0)
		{
			while (split[n])
				++n;
			face.nb = n - 1;
			face.sommets = (t_vec3*)malloc(sizeof(t_vec3) * face.nb);
			face.normales = (t_vec3*)malloc(sizeof(t_vec3) * face.nb);
			face.textures = (t_vec2*)malloc(sizeof(t_vec2) * face.nb);
			if (!face.sommets || !face.normales || !face.textures)
				return (0);
			i = 1;
			while (i <= face.nb)
			{
				if ((size_t)atoi(split[i]) > components.n_sommets
						|| (size_t)atoi(ft_strrchr(split[i], '/') + 1) > components.n_normales)
					return (0);
				tmp = components.sommets[atoi(split[i]) - 1];
				face.sommets[i - 1] = tmp;
				face.normales[i - 1] = components.normales[atoi(ft_strrchr(split[i], '/') + 1) - 1];
				++i;
			}
			object->faces[components.n_faces] = face;
			++components.n_faces;
		}
		free_strsplit(split);
	}

	free(components.sommets);
	free(components.textures);
	free(components.normales);
	return (TRUE);
}

t_object	*parse_wavefront_file(char *filename)
{
	static t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = POLYGONS;
	ft_strcpy(object.name, get_el_type_char(&object));
	object.operation = '0';
	if (!start_parsing(&object, filename))
		return (FALSE);
	return (&object);
}
