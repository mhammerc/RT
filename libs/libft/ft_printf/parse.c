/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:52:12 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:15:24 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

static void		init(char const **s, t_printf_info **info,
		char const *conversion, t_app *app)
{
	*s = conversion;
	*info = (t_printf_info*)malloc(sizeof(t_printf_info));
	ft_bzero(*info, sizeof(t_printf_info));
	(*info)->prec = -1;
	(*info)->pad = ' ';
	(*info)->app = app;
}

static void		apply_func2(t_printf_info *info, char **line, int *i, long r)
{
	t_list	*list;

	(void)i;
	list = (t_list*)malloc(sizeof(t_list));
	list->content = *line;
	list->content_size = r;
	list->next = NULL;
	ft_lstpushback(&info->app->results, list);
}

static int		apply_func(t_printf_info *info, char const *s,
		char **line, char const *conversion)
{
	t_printf_func	func;
	long			a;
	int				r;
	int				i;

	func = search_conversion(info->app, info->spec);
	if (!func)
		func = printf_print_percentage;
	if (func && *s)
	{
		if (func != printf_print_percentage)
		{
			a = va_arg(*(info->app->ap), long);
			r = func(&a, info, line);
		}
		else
			r = func(&r, info, line);
		apply_func2(info, line, &i, r);
		info->app->written_chars += r;
		free(info);
		return (int)(s - conversion + 1);
	}
	free(info);
	info->app->written_chars += 0;
	return (int)(s - conversion);
}

static int		conversion_found(char const *conversion, t_app *app)
{
	t_printf_info	*info;
	char			*line;
	char const		*s;

	init(&s, &info, conversion, app);
	while (1)
	{
		if (parse10(&s, info))
			continue;
		else if (parse11(&s, info))
			continue;
		else if (parse12(&s, info))
			continue;
		else if (parse13(&s, info))
			continue;
		else if (parse14(&s, info))
			continue;
		info->spec = *s;
		break ;
	}
	return (apply_func(info, s, &line, conversion));
}

void			parse(char const *format, t_app *app)
{
	t_vector2i	i;
	char		str[256];

	i.x = 0;
	i.y = 0;
	ft_bzero(str, 256);
	while (format[i.x])
	{
		if (format[i.x] == '%')
		{
			ft_lstpushback(&app->results, ft_lstnew(str, ft_strlen(str)));
			ft_bzero(str, 256);
			i.y = 0;
			++i.x;
			i.x += conversion_found(format + i.x, app);
			continue;
		}
		parse2(&i, app, str, format);
	}
	ft_lstpushback(&app->results, ft_lstnew(str, ft_strlen(str)));
}
