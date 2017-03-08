/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:08:18 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:12:02 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "rtv1.h"

/*
** Color tab constructor, img is a mlx image pointer
** @return the created color
*/

t_color		*color_tab_new(int w, int h, int *img)
{
	t_color	*tab;
	int		i;
	int		len;

	if (NULL == (tab = (t_color*)malloc(sizeof(t_color) * w * h))
		|| NULL == img)
		return (NULL);
	i = -1;
	len = w * h;
	while (++i < len)
	{
		tab[i].img = &(img[i]);
		tab[i].r = 0.0;
		tab[i].g = 0.0;
		tab[i].b = 0.0;
	}
	return (tab);
}

/*
** Reset a color tab
*/

void		color_tab_reset(int w, int h, t_color *tab)
{
	int		i;
	int		len;

	i = -1;
	len = w * h;
	while (++i < len)
	{
		*(tab[i].img) = 0;
		tab[i].r = 0.0;
		tab[i].g = 0.0;
		tab[i].b = 0.0;
	}
	return ;
}

/*
** Find max value in color tab
** @return max value in tab
*/

static t_f	color_tab_max(int w, int h, t_color *t)
{
	t_f		max;
	int		i;
	int		len;

	len = w * h;
	i = -1;
	max = 0.;
	while (++i < len)
	{
		max = fmax(max, t[i].r);
		max = fmax(max, t[i].g);
		max = fmax(max, t[i].b);
	}
	return (max);
}

/*
** Normalize a color tab and write into image
*/

void		color_tab_normalize(int w, int h, t_color *t)
{
	t_f		invmax;
	int		i;
	int		len;

	i = -1;
	len = w * h;
	invmax = 1. / color_tab_max(w, h, t);
	while (++i < len)
	{
		*(t[i].img) = colorcomp_to_rgb(t[i].r * 255 * invmax,
										t[i].g * 255 * invmax,
										t[i].b * 255 * invmax);
	}
	return ;
}
