/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:14:08 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:14:15 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_p.h"

void			parse2(t_vector2i *i, t_app *app, char *str, char const *format)
{
	if (i->y == 255)
	{
		ft_lstpushback(&app->results, ft_lstnew(str, ft_strlen(str)));
		ft_bzero(str, 256);
		i->y = 0;
	}
	str[i->y] = format[i->x];
	++i->y;
	++app->written_chars;
	++i->x;
}
