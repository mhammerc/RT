/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_printf_hexadecimal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:06:50 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 21:54:16 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"
#include <limits.h>

static int					count_digits2(unsigned long long n)
{
	if (n < 16)
		return (1);
	return (1 + count_digits2(n / 16));
}

static int					count_digits(unsigned long long n,
		t_printf_info *info)
{
	int length;

	length = count_digits2(n);
	if (info->alt && n != 0)
		length += 2;
	if (n == 0 && info->prec == 0)
		return (-1);
	if ((length <= info->prec && (!info->alt || n == 0)) ||
			(length <= info->prec + 2 && (info->alt && n != 0)))
		return (info->alt && n != 0 ? info->prec + 2 : info->prec);
	return (length);
}

static void					print_digits(char *line, unsigned long long n,
		int length, t_printf_info *info)
{
	int					len;
	int					i;
	char				*base;
	static char			*alt;

	base = (info->spec == 'x' ? "0123456789abcdef" : "0123456789ABCDEF");
	alt = NULL;
	if (info->alt)
		alt = (info->spec == 'x' ? "0x" : "0X");
	if (n == 0 && info->prec == 0)
		return ;
	len = count_digits2(n);
	if (len < length)
	{
		ft_memset(line, '0', length - len);
		line += length - len;
	}
	if (alt && n != 0)
		ft_memcpy(line - length + len, alt, 2);
	i = -1;
	while ((++i) < len)
	{
		line[len - i - 1] = base[n % 16];
		n = (n - n % 16) / 16;
	}
}

static unsigned long long	convert(void *param, t_printf_info *info)
{
	unsigned long long	n;

	if (info->is_long)
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

int							printf_print_hexadecimal(void *param,
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
