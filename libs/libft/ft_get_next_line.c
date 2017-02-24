/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:52:04 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/16 14:07:06 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		read_if_not_available(int const fd, t_reader *reader)
{
	if (fd < 0 || fd == 1 || fd == 2)
		return (-1);
	if (read(fd, reader->text, 0) == -1)
		return (-1);
	if (reader->position >= (size_t)reader->available)
		reader->available = 0;
	if (!reader->available)
	{
		reader->available = read(fd, reader->text, BUFF_SIZE);
		reader->position = 0;
		reader->text[reader->available] = '\0';
	}
	return (reader->available);
}

static int		concat_result(char **old_string, char **line, t_reader *reader)
{
	if (*old_string)
	{
		free(*old_string);
		*old_string = NULL;
	}
	*old_string = *line;
	*line = ft_strnew(reader->available + 1 + ft_strlen(*old_string));
	if (!*line)
		return (-1);
	ft_strcpy(*line, *old_string);
	ft_strcat(*line, reader->text);
	return (1);
}

static int		create_result(char **line, t_reader *reader)
{
	*line = ft_strnew(reader->available + 1 - reader->position);
	if (!*line)
		return (-1);
	ft_strcpy(*line, reader->text + reader->position);
	return (0);
}

static int		finish_and_return(char **old_string, t_reader *reader, char *c,
		char **line)
{
	*c = '\0';
	if (*old_string == NULL)
		reader->position += c - *line + 1;
	else
	{
		reader->position += c - *line + 1 - ft_strlen(*old_string);
		free(*old_string);
		*old_string = NULL;
	}
	return (1);
}

int				ft_get_next_line(int const fd, char **line)
{
	static t_reader reader = { 0, 0, {0} };
	char			*c;
	char			*old_string;

	if (line)
		*line = NULL;
	old_string = NULL;
	while (1)
	{
		if (read_if_not_available(fd, &reader) == -1)
			return (-1);
		if (reader.available == 0 && (!*line || ft_strlen(*line) == 0))
			return (0);
		if (reader.available == 0 && *line && ft_strlen(*line) != 0)
			return (1);
		if (*line != NULL && concat_result(&old_string, line, &reader) == -1)
			return (-1);
		else if (*line == NULL && create_result(line, &reader) == -1)
			return (-1);
		c = ft_strchr(*line, '\n');
		if (c)
			return (finish_and_return(&old_string, &reader, c, line));
		reader.available = 0;
	}
}
