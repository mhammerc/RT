/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:37:25 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 10:37:26 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"

int			copy_position(t_object *object, t_faces_components *components,
		char **split)
{
	t_vec3	tmp;

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
		components->sommets[components->n_sommets++] = tmp;
	}
	return (1);
}

int			copy_texture(t_faces_components *components,
		char **split)
{
	t_vec2	tmp;

	if (ft_strcmp(split[0], "vt") == 0)
	{
		if (!split[1] || !split[2])
			return (0);
		tmp.x = atof(split[1]);
		tmp.y = atof(split[2]);
		components->textures[components->n_textures++] = tmp;
	}
	return (1);
}

int			copy_normales(t_faces_components *components,
		char **split)
{
	t_vec3	tmp;

	if (ft_strcmp(split[0], "vn") == 0)
	{
		if (!split[1] || !split[2] || !split[3])
			return (0);
		tmp.x = atof(split[1]);
		tmp.y = atof(split[2]);
		tmp.z = atof(split[3]);
		components->normales[components->n_normales++] = tmp;
	}
	return (1);
}

int			copy_components2(t_object *object, t_faces_components *components,
		char **split)
{
	if ((split[0] && split[0][0] == '#') || !split[0])
		return (1);
	if (!copy_position(object, components, split))
		return (0);
	if (!copy_texture(components, split))
		return (0);
	if (!copy_normales(components, split))
		return (0);
	return (1);
}

int			copy_components(t_object *object, char *filename,
		t_faces_components *components)
{
	char	*line;
	char	**split;
	FILE	*fp;
	ssize_t	ret;
	size_t	n;

	fp = fopen(filename, "r");
	if (!fp)
		return (0);
	line = NULL;
	while ((ret = getline(&line, &n, fp)) != -1)
	{
		line[ret - 1] = 0;
		split = ft_strsplit(line, ' ');
		if (!copy_components2(object, components, split))
			return (0);
		free(line);
		line = NULL;
		strsplit_free(split);
	}
	fclose(fp);
	return (1);
}
