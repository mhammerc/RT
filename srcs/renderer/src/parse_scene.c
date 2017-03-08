/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:29:54 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 19:19:27 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libft.h>
#include "rtv1.h"

/*
** Parse line from scene file, fills in scene attribute
** @return Positive int if ok, 0 otherwise
*/

static int		parse_line(t_scene *sce, char *line, int w, int h)
{
	char		**t;
	int			ret;

	t = ft_strsplit(line, ' ');
	if (t == NULL)
		ret = 0;
	else if (*t == NULL || **t == '#')
		ret = 1;
	else if (0 == ft_strcmp("Ambiant", *t))
		ret = parse_ambiant(sce, t + 1);
	else if (0 == ft_strcmp("Camera", *t))
		ret = parse_camera(sce, t + 1, w, h);
	else if (0 == ft_strcmp("Light", *t))
		ret = parse_light(sce, t + 1);
	else if (0 == ft_strcmp("Object", *t))
		ret = parse_object(sce, t + 1);
	else
		ret = 0;
	ft_strtabdel(t);
	return (ret);
}

/*
** Check if a scene has at least one camera, one object, and one light
** @return 1 if ok, 0 otherwise
*/

static int		check_scene(t_scene *sce)
{
	if (ft_lstsize(sce->obj) == 0
		|| ft_lstsize(sce->light) == 0
		|| sce->cam == NULL)
		return (0);
	return (1);
}

/*
** Parse scene file
** @return a scene struct given a scene file or null
*/

t_scene			*parse_scene(char *filename, int w, int h)
{
	int			fd;
	char		*line;
	t_scene		*sce;
	char		*start;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_exit("Error while opening scene file", EXIT_FAILURE);
	if ((sce = (t_scene*)ft_memalloc(sizeof(t_scene))) == NULL)
		ft_exit("Error while creating new scene", EXIT_FAILURE);
	while (get_next_line(fd, &line) > 0)
	{
		start = line;
		while (*start == ' ' || *start == '\t')
			++start;
		if (0 == parse_line(sce, start, w, h) || 0 == ft_strlen(start))
			ft_exit("Incorrect formating in scene file", EXIT_SUCCESS);
		free(line);
	}
	free(line);
	close(fd);
	if (0 == check_scene(sce))
		ft_exit("Missing element(s) in scene file", EXIT_SUCCESS);
	return (sce);
}
