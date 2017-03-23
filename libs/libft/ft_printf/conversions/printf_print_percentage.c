/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_percentage.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:57:45 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 21:58:21 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"

int	printf_print_percentage(void *param, t_printf_info *info, char **line)
{
	unsigned int	c;

	(void)param;
	c = info->spec;
	*line = monloc(sizeof(char) * (info->width + 2));
	if (!*line)
		return (0);
	if (!info->left)
	{
		ft_memset(*line, info->pad, info->width);
		(*line)[info->width ? info->width - 1 : 0] = c;
	}
	else
	{
		ft_memset(*line, ' ', info->width);
		*(*line) = c;
	}
	(*line)[info->width ? info->width + 1 : 1] = 0;
	return (info->width ? info->width : 1);
}
