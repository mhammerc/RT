/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_octal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:56:31 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 21:56:46 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"
#include <limits.h>

static int					count_digits2(unsigned long long n)
{
	if (n < 8)
		return (1);
	return (1 + count_digits2(n / 8));
}

static int					count_digits(unsigned long long n,
		t_printf_info *info)
{
	int length;

	length = count_digits2(n);
	if (info->alt)
		length += 1;
	if (n == 0 && info->prec == 0 && !info->alt)
		return (-1);
	if (n == 0 && (info->prec == 0 || info->prec == -1) && info->alt)
		return (1);
	if (length <= info->prec)
		return (info->alt && n != 0 ? info->prec + 0 : info->prec);
	return (length);
}

static void					print_digits(char *line, unsigned long long n,
		int length, t_printf_info *info)
{
	int					len;
	int					i;
	char				*alt;

	if (info->alt || (n == 0 && info->prec == -1))
		alt = "0";
	else
		alt = NULL;
	if (n == 0 && info->prec == 0 && !info->alt)
		return ;
	len = count_digits2(n);
	if (len < length)
	{
		ft_memset(line, '0', length - len);
		line += length - len;
	}
	i = 0;
	if (alt)
		ft_memcpy(line - length + len, alt, 1);
	while (i < len && (n != 0 || (n == 0 && info->prec == 1)))
	{
		line[len - i - 1] = n % 8 + 48;
		n = (n - n % 8) / 8;
		++i;
	}
}

static unsigned long long	convert(void *param, t_printf_info *info)
{
	unsigned long long	n;

	if (info->is_long || info->spec == 'O')
		n = *(unsigned long*)param;
	else if (info->is_short)
		n = *(unsigned short*)param;
	else if (info->is_char)
		n = *(unsigned char*)param;
	else if (info->is_long_double)
		n = *(unsigned long long*)param;
	else if (info->is_j)
		n = *(uintmax_t*)param;
	else if (info->is_z)
		n = *(ssize_t*)param;
	else
		n = *(unsigned int*)param;
	info->showsign = 0;
	info->space = 0;
	return (n);
}

int							printf_print_octal(void *param,
		t_printf_info *info, char **line)
{
	unsigned long long	n;
	int					length;

	n = convert(param, info);
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
