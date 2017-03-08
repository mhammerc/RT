/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 21:58:38 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:39:57 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "rtv1.h"

/*
** Check size of tab of string + if all strings are numeric
** @return 1 if all numeric and expected size, 0 otherwise
*/

int			check_numeric(int size, char **t)
{
	int		i;

	if (ft_strtablen(t) != size)
		return (0);
	i = 0;
	while (t[i])
	{
		if (!ft_isnumeric(t[i]))
			return (0);
		++i;
	}
	return (1);
}

/*
** Run raytracing and display image to window
** @return nothing
*/

void		draw(t_env *e)
{
	color_tab_reset(e->w, e->h, e->color);
	rt(e);
	color_tab_normalize(e->w, e->h, e->color);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

int			int_checkbounds(int x, int min, int max)
{
	if (x < min || x > max)
		return (0);
	return (1);
}

t_f			float_checkbounds(t_f x, t_f min, t_f max)
{
	if (x < min || x > max)
		return (0);
	return (1);
}
