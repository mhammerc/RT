/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:59:37 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/17 17:02:44 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

t_printf_func	search_conversion(t_app *app, int code)
{
	t_list				*list;
	t_printf_conversion	*conversion;

	list = app->conversions;
	while (list->content)
	{
		conversion = (t_printf_conversion*)list->content;
		if (conversion->code == code)
			return (conversion->func);
		list = list->next;
	}
	return (0);
}
