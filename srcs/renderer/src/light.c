/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 20:16:35 by vfour             #+#    #+#             */
/*   Updated: 2017/02/02 18:06:21 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

/*
** Create light object given split string from scene file
** @return pointer to created light
*/

t_light		*light_new(char **t)
{
	t_light	*light;
	t_f		color_normalize;

	light = NULL;
	if (NULL == (light = (t_light*)malloc(sizeof(t_light))))
		ft_exit("Light malloc failed", EXIT_FAILURE);
	light->pos = (t_vec3){ft_atof(*t), ft_atof(*(t + 1)), ft_atof(*(t + 2))};
	color_normalize = 1. / 255.;
	light->color.r = (t_f)ft_atoi(*(t + 3)) * color_normalize;
	light->color.g = (t_f)ft_atoi(*(t + 4)) * color_normalize;
	light->color.b = (t_f)ft_atoi(*(t + 5)) * color_normalize;
	light->i = ft_atof(*(t + 6));
	light->color.img = NULL;
	return (light);
}
