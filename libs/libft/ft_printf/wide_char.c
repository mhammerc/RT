/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 23:46:55 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 23:46:58 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

static int	wchar4(unsigned int nb, char *line)
{
	unsigned char	c;

	c = 0x000000F0 | ((nb << 11) >> 29);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 14) >> 26);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 20) >> 26);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 26) >> 26);
	*line = c;
	++line;
	return (4);
}

static int	wchar3(unsigned int nb, char *line)
{
	unsigned char	c;

	c = 0x000000E0 | ((nb << 16) >> 28);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 20) >> 26);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 26) >> 26);
	*line = c;
	++line;
	return (3);
}

static int	wchar2(unsigned int nb, char *line)
{
	unsigned char	c;

	c = 0x000000C0 | ((nb << 21) >> 27);
	*line = c;
	++line;
	c = 0x00000080 | ((nb << 26) >> 26);
	*line = c;
	++line;
	return (2);
}

int			compute_wchar(unsigned int nb, char *line)
{
	unsigned char	c;

	if (nb < 127)
	{
		c = nb;
		*line = c;
		return (1);
	}
	if (nb >= 128 && nb <= 2047)
		return (wchar2(nb, line));
	if ((nb >= 2048 && nb <= 55295) || (nb >= 57344 && nb <= 65535))
		return (wchar3(nb, line));
	if ((nb >= 65536 && nb <= 196607) || (nb >= 917504 && nb <= 1114111))
		return (wchar4(nb, line));
	return (0);
}

int			count_wchar(unsigned int nb)
{
	if (nb < 127)
		return (1);
	else if (nb >= 128 && nb <= 2047)
		return (2);
	else if ((nb >= 2048 && nb <= 55295) || (nb >= 57344 && nb <= 65535))
		return (3);
	else if ((nb >= 65536 && nb <= 196607) || (nb >= 917504 && nb <= 1114111))
		return (4);
	return (0);
}
