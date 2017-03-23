/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:29:37 by racousin          #+#    #+#             */
/*   Updated: 2017/03/23 10:29:38 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "shared.h"

static void		filter_black_and_white(t_vec3 *light, int len)
{
	int		i;
	double	tmp2;

	i = -1;
	while (++i < len)
	{
		tmp2 = light[i].x + light[i].y + light[i].z;
		tmp2 /= 3;
		light[i].x = tmp2;
		light[i].y = tmp2;
		light[i].z = tmp2;
	}
}

static void		filter_sepia(t_vec3 *light, int len)
{
	int		i;
	t_vec3	tmp;

	i = -1;
	while (++i < len)
	{
		tmp.x = (light[i].x * .393) + (light[i].y * .769) + (light[i].z * .189);
		tmp.y = (light[i].x * .349) + (light[i].y * .686) + (light[i].z * .168);
		tmp.z = (light[i].x * .272) + (light[i].y * .534) + (light[i].z * .131);
		light[i] = tmp;
	}
}

void			light_apply_filters(t_scene *sce, t_vec3 *light, int w, int h)
{
	int		len;

	len = w * h;
	if (sce->filter == BLACK_WHITE)
		filter_black_and_white(light, len);
	if (sce->filter == SEPIA)
		filter_sepia(light, len);
}
