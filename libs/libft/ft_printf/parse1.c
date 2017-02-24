/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:57:16 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 23:47:38 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

int	parse10(char const **s, t_printf_info *info)
{
	if (**s == '-')
	{
		info->left = 1;
		++(*s);
		return (1);
	}
	if (**s == '+')
	{
		info->showsign = 1;
		++(*s);
		return (1);
	}
	if (**s == '#')
	{
		info->alt = 1;
		++(*s);
		return (1);
	}
	if (**s == '0')
	{
		info->pad = '0';
		++(*s);
		return (1);
	}
	return (0);
}

int	parse11(char const **s, t_printf_info *info)
{
	if (**s == ' ')
	{
		info->space = 1;
		++(*s);
		return (1);
	}
	if (ft_isdigit(**s))
	{
		info->width = ft_atoi(*s);
		while (ft_isdigit(**s))
			++(*s);
		return (1);
	}
	if (**s == '.')
	{
		++(*s);
		if (ft_isdigit(**s))
			info->prec = ft_atoi(*s);
		else
			info->prec = 0;
		while (ft_isdigit(**s))
			++(*s);
		return (1);
	}
	return (0);
}

int	parse12(char const **s, t_printf_info *info)
{
	if (**s == 'q')
	{
		++(*s);
		info->is_long_double = 1;
		return (1);
	}
	if (**s == 'h')
	{
		if (*((*s) + 1) == 'h')
		{
			info->is_char = 1;
			(*s) += 2;
		}
		else
		{
			info->is_short = 1;
			++(*s);
		}
		return (1);
	}
	return (0);
}

int	parse13(char const **s, t_printf_info *info)
{
	if (**s == 'l')
	{
		if (*((*s) + 1) == 'l')
		{
			info->is_long_double = 1;
			*s += 2;
		}
		else
		{
			info->is_long = 1;
			++*s;
		}
		return (1);
	}
	if (**s == 'j')
	{
		++(*s);
		info->is_j = 1;
		return (1);
	}
	return (0);
}

int	parse14(char const **s, t_printf_info *info)
{
	if (**s == 'L')
	{
		++(*s);
		info->is_long_double = 1;
		return (1);
	}
	if (**s == 'z')
	{
		++(*s);
		info->is_z = 1;
		return (1);
	}
	return (0);
}
