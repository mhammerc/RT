/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:39:28 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 22:39:29 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"

void	compute(char **line, unsigned int c, t_printf_info *info, size_t size)
{
	*line = malloc(sizeof(char) * (info->width + size + 1));
	if (!*line)
		return ;
	if (!info->left)
	{
		ft_memset(*line, info->pad, info->width);
		if (info->is_long)
			compute_wchar(c, info->width ? (*line) + info->width - 1 : (*line));
		else
			(*line)[info->width ? info->width - 1 : 0] = c;
	}
	else
	{
		ft_memset(*line, ' ', info->width);
		if (info->is_long)
			compute_wchar(c, (*line));
		else
			**line = c;
	}
}

int		printf_print_char(void *param, t_printf_info *info, char **line)
{
	unsigned int	c;
	size_t			size;

	if ((info->spec == 'c' && info->is_long) || info->spec == 'C')
	{
		c = *(wint_t*)param;
		info->is_long = 1;
	}
	else
		c = *(unsigned char*)param;
	size = info->is_long ? count_wchar(c) : 1;
	compute(line, c, info, size);
	(*line)[info->width ? info->width + size : size] = 0;
	return (info->width ? info->width + size - 1 : size);
}
