/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:11:03 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/21 11:02:30 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

static void	init_conversions(t_app *app)
{
	app->conversions = ft_lstnew(0, 0);
	register_printf_function((int)'s', printf_print_string, app);
	register_printf_function((int)'S', printf_print_string, app);
	register_printf_function((int)'%', printf_print_percentage, app);
	register_printf_function((int)'c', printf_print_char, app);
	register_printf_function((int)'C', printf_print_char, app);
	register_printf_function((int)'d', printf_print_decimal_signed, app);
	register_printf_function((int)'i', printf_print_decimal_signed, app);
	register_printf_function((int)'D', printf_print_decimal_signed, app);
	register_printf_function((int)'u', printf_print_decimal_unsigned, app);
	register_printf_function((int)'U', printf_print_decimal_unsigned, app);
	register_printf_function((int)'x', printf_print_hexadecimal, app);
	register_printf_function((int)'X', printf_print_hexadecimal, app);
	register_printf_function((int)'o', printf_print_octal, app);
	register_printf_function((int)'O', printf_print_octal, app);
	register_printf_function((int)'p', printf_print_pointer, app);
}

int			ft_printf(char const *format, ...)
{
	static t_app	app = { 0, 0, 0, 0 };
	t_list			*list;

	if (app.conversions == NULL)
		init_conversions(&app);
	app.written_chars = 0;
	app.ap = (va_list*)malloc(sizeof(va_list));
	va_start(*app.ap, format);
	parse(format, &app);
	va_end(*app.ap);
	free(app.ap);
	list = app.results;
	while (list)
	{
		write(1, (char*)list->content, list->content_size);
		list = list->next;
	}
	ft_lstdel(&app.results, ft_classicfree);
	return (app.written_chars);
}

int			ft_dprintf(int fd, char const *format, ...)
{
	static t_app	app = { 0, 0, 0, 0 };
	t_list			*list;

	if (app.conversions == NULL)
		init_conversions(&app);
	app.written_chars = 0;
	app.ap = (va_list*)malloc(sizeof(va_list));
	va_start(*app.ap, format);
	parse(format, &app);
	va_end(*app.ap);
	free(app.ap);
	list = app.results;
	while (list)
	{
		write(fd, (char*)list->content, list->content_size);
		list = list->next;
	}
	ft_lstdel(&app.results, ft_classicfree);
	return (app.written_chars);
}

static void	ft_sprintf2(char **str, size_t len, t_list **list, t_app *app)
{
	ft_bzero(*str, len + 1);
	*list = app->results;
	while (*list)
	{
		ft_strncat(*str, (char*)(*list)->content, (*list)->content_size);
		(*list) = (*list)->next;
	}
	ft_lstdel(&app->results, ft_classicfree);
}

int			ft_sprintf(char **str, char const *format, ...)
{
	static t_app	app = { 0, 0, 0, 0 };
	t_list			*list;
	size_t			len;

	if (app.conversions == NULL)
		init_conversions(&app);
	app.written_chars = 0;
	app.ap = (va_list*)malloc(sizeof(va_list));
	va_start(*app.ap, format);
	parse(format, &app);
	va_end(*app.ap);
	free(app.ap);
	len = 0;
	list = app.results;
	while (list)
	{
		len += list->content_size;
		list = list->next;
	}
	*str = (char*)malloc(sizeof(char) * (len + 1));
	if (!*str)
		return (0);
	ft_sprintf2(str, len, &list, &app);
	return (app.written_chars);
}
