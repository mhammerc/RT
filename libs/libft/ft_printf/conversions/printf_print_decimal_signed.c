/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_printf_decimal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:06:50 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 21:05:22 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_p.h"
#include <limits.h>

static int			count_digits2(long long n)
{
	if (n < 0)
		return (count_digits2((n == LLONG_MIN) ? LLONG_MAX : -n));
	if (n < 10)
		return (1);
	return (1 + count_digits2(n / 10));
}

static int			count_digits(long long n, t_printf_info *info)
{
	int length;

	length = count_digits2(n);
	if (n == 0 && info->prec == 0)
		return (-1);
	if (n < 0 || (n >= 0 && (info->showsign || info->space)))
		length += 1;
	if (length <= info->prec)
	{
		if (n < 0 || (n >= 0 && (info->showsign || info->space)))
			return (info->prec + 1);
		return (info->prec);
	}
	return (length);
}

static void			print_digits(char *line, long long n, int length,
		t_printf_info *info)
{
	unsigned long long	n2;
	int					len;
	int					i;

	if (n == 0 && info->prec == 0)
		return ;
	n2 = (unsigned long long)n;
	if (n < 0 || (n >= 0 && (info->showsign || info->space)))
	{
		if (n < 0)
			*(line++) = '-';
		else
			*(line++) = (info->showsign ? '+' : ' ');
		--length;
		if (n < 0)
			n2 = (n == LLONG_MIN ? (t_ull)LLONG_MAX + (t_ull)1 : (t_ull)-n);
	}
	len = count_digits2(n);
	ft_memset(line, '0', (len < length ? length - len : 0));
	i = -1;
	while (++i < len)
	{
		line[len < length ? length - i - 1 : len - i - 1] = (n2 % 10) + 48;
		n2 = (n2 - n2 % 10) / 10;
	}
}

static long long	convert(void *param, t_printf_info *info)
{
	signed long long	n;

	if (info->is_long || info->spec == 'D')
		n = *(signed long*)param;
	else if (info->is_j)
		n = *(intmax_t*)param;
	else if (info->is_z)
		n = *(size_t*)param;
	else if (info->is_short)
		n = *(short*)param;
	else if (info->is_char)
		n = *(char*)param;
	else if (info->is_long_double)
		n = *(long long*)param;
	else
		n = *(signed int*)param;
	return (n);
}

int					printf_print_decimal_signed(void *param,
		t_printf_info *info, char **line)
{
	signed long long	n;
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
		print_digits((info->left ? *line : (*line + info->width - length)),
				n, length, info);
	}
	else
		print_digits(*line, n, length, info);
	return (length < info->width ? info->width : length);
}
