/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 14:07:36 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/23 00:55:07 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"

static void	print(char **line, t_printf_info *info, int is_valid, char *s)
{
	*line = (char*)monloc(sizeof(char) * (info->prec + info->width + 1));
	if (info->width != 0 && info->width - info->prec > 0 && !info->left)
	{
		ft_memset(*line, info->pad, info->width - info->prec);
		(*line)[info->width - info->prec] = 0;
		if (is_valid)
			ft_strncat((*line), s, info->prec);
	}
	else if (info->width != 0 && info->width - info->prec > 0 && info->left)
	{
		(*line)[0] = 0;
		if (is_valid)
			ft_strncat(*line, s, info->prec);
		ft_memset(*line + info->prec, ' ', info->width - info->prec);
		(*line)[info->prec + info->width] = 0;
	}
	else
	{
		(*line)[0] = 0;
		if (is_valid)
			ft_strncat(*line, s, info->prec);
	}
	if (info->is_long && is_valid)
		free(s);
}

static int	compute(void *param, t_printf_info *info, int *i, char **s)
{
	int	count;
	int	z;
	int	j;

	*i = 0;
	count = 0;
	while ((*(wchar_t**)param)[*i])
	{
		z = count;
		count += count_wchar((*(wchar_t**)param)[*i]);
		if (info->prec != -1 && count > info->prec)
		{
			count = z;
			--(*i);
			break ;
		}
		++(*i);
	}
	*s = (char*)monloc(sizeof(char) * (count + 1));
	(*s)[count] = 0;
	*i = -1;
	j = 0;
	while ((*(wchar_t**)param)[++(*i)])
		j += compute_wchar((*(wchar_t**)param)[*i], *s + j);
	return (count);
}

static int	die(char **line)
{
	*line = ft_strdup("(null)");
	return (6);
}

int			printf_print_string(void *param, t_printf_info *info, char **line)
{
	char	*s;
	int		i;
	int		count;
	int		is_valid;

	is_valid = !!(*(int**)param);
	if (!(*(void**)param) && info->prec == -1)
		return (die(line));
	if ((info->is_long || info->spec == 'S') && is_valid && (info->is_long = 1))
		count = compute(param, info, &i, &s);
	else
		s = *(char**)param;
	if (info->prec != -1 && is_valid)
	{
		i = 0;
		while (s[i] && i < info->prec && ((info->is_long && i < count)
					|| !info->is_long))
			++i;
		info->prec = i;
	}
	else if (is_valid)
		info->prec = ft_strlen(s);
	print(line, info, is_valid, s);
	return (info->width > info->prec ? info->width : info->prec);
}
