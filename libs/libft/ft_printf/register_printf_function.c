/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_printf_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:17:32 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/22 22:54:09 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

int		register_printf_function(int code, t_printf_func func, void *app_)
{
	t_app				*app;
	t_list				*conversions;
	t_printf_conversion	*new_conversion;

	app = (t_app*)app_;
	conversions = app->conversions;
	while (conversions->next)
		conversions = conversions->next;
	conversions->next = ft_lstnew(0, 0);
	if (!conversions->next)
		return (0);
	new_conversion = (t_printf_conversion*)monloc(sizeof(t_printf_conversion));
	if (!new_conversion)
		return (0);
	new_conversion->code = code;
	new_conversion->func = func;
	conversions->content = (void*)new_conversion;
	conversions->content_size = sizeof(t_printf_conversion);
	return (1);
}
