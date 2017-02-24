/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 16:52:48 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:14:39 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_P_H
# define FT_PRINTF_P_H

# include "ft_printf.h"

# include <stdarg.h>
# include <stdlib.h>
# include <inttypes.h>
# include <wchar.h>

# include "../libft.h"

typedef unsigned long long	t_ull;

typedef struct				s_app
{
	t_list				*conversions;
	t_list				*results;
	va_list				*ap;
	int					written_chars;
}							t_app;

typedef struct				s_printf_info
{
	int					prec;
	int					width;
	unsigned int		spec;
	unsigned int		is_long_double;
	unsigned int		is_char;
	unsigned int		is_short;
	unsigned int		is_long;
	unsigned int		is_j;
	unsigned int		is_z;
	unsigned int		alt;
	unsigned int		space;
	unsigned int		left;
	unsigned int		showsign;
	unsigned int		group;
	unsigned int		extra;
	unsigned int		wide;
	unsigned int		pad;
	t_app				*app;
}							t_printf_info;

typedef struct				s_vector2i
{
	int					x;
	int					y;
}							t_vector2i;

typedef	int	(*t_printf_func)(void*, t_printf_info*, char**);

typedef struct				s_printf_conversion
{
	int					code;
	t_printf_func		func;
}							t_printf_conversion;

int							printf_print_string(void *param,
		t_printf_info *info, char **line);
int							printf_print_wide_string(void *param,
		t_printf_info *info, char **line);
int							printf_print_decimal_signed(void *param,
		t_printf_info *info, char **line);
int							printf_print_decimal_unsigned(void *param,
		t_printf_info *info, char **line);
int							printf_print_hexadecimal(void *param,
		t_printf_info *info, char **line);
int							printf_print_octal(void *param,
		t_printf_info *info, char **line);
int							printf_print_pointer(void *param,
		t_printf_info *info, char **line);
int							printf_print_percentage(void *param,
		t_printf_info *info, char **line);
int							printf_print_char(void *param,
		t_printf_info *info, char **line);

int							register_printf_function(int code,
		t_printf_func func, void *app);
void						parse(char const *format, t_app *app);
t_printf_func				search_conversion(t_app *app, int code);

int							compute_wchar(unsigned int nb, char *line);
int							count_wchar(unsigned int nb);

void						parse2(t_vector2i *i, t_app *app, char *str,
		char const *format);
int							parse10(char const **s, t_printf_info *info);
int							parse11(char const **s, t_printf_info *info);
int							parse12(char const **s, t_printf_info *info);
int							parse13(char const **s, t_printf_info *info);
int							parse14(char const **s, t_printf_info *info);

#endif
