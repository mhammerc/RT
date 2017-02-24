/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_pointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:00:17 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 22:00:38 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"
#include <limits.h>

static int					count_digits2(uintptr_t n)
{
	if (n < 16)
		return (1);
	return (1 + count_digits2(n / 16));
}

static int					count_digits(uintptr_t n,
		t_printf_info *info)
{
	int length;

	length = count_digits2(n);
	if (n == 0 && info->prec == 0)
		length = 0;
	if (length <= info->prec)
		return (info->prec + 2);
	return (length + 2);
}

static void					print_digits(char *line, uintptr_t n,
		int length, t_printf_info *info)
{
	int					len;
	int					i;
	char				*base;
	char				*alt;

	base = "0123456789abcdef";
	alt = "0x";
	len = count_digits2(n);
	if (n == 0 && info->prec == 0)
		len = 0;
	if (len < length)
	{
		ft_memset(line, '0', length);
		line += length - len;
	}
	i = 0;
	ft_memcpy(line - length + len, alt, 2);
	while (i < len)
	{
		line[len - i - 1] = base[n % 16];
		n = (n - n % 16) / 16;
		++i;
	}
}

int							printf_print_pointer(void *param,
		t_printf_info *info, char **line)
{
	uintptr_t			n;
	int					length;

	n = *(uintptr_t*)param;
	length = count_digits(n, info);
	if ((length < info->width && info->pad == '0' && !info->left &&
				info->prec == -1) || (length == -1 && info->width == 0))
		length = info->width;
	length = (length == -1 ? 0 : length);
	*line = ft_strnew((length < info->width ? info->width : length) + 1);
	if (length < info->width && (info->left || info->pad != '0' ||
				(info->pad == '0' && info->prec == -1)))
		ft_memset((!info->left ? *line : *line + length), (!info->left ?
					info->pad : ' '), info->width - length);
	if (info->width && info->width > length)
	{
		ft_memset(*line, ' ', info->width - length);
		print_digits((info->left ? *line : (*line + info->width - length)), n,
				length, info);
	}
	else
		print_digits(*line, n, length, info);
	return (length < info->width ? info->width : length);
}
