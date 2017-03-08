/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 22:17:03 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:09:34 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "rtv1.h"

static int	check_ambiant(t_light amb)
{
	if (!float_checkbounds(amb.color.r, 0, 1)
		|| !float_checkbounds(amb.color.g, 0, 1)
		|| !float_checkbounds(amb.color.b, 0, 1)
		|| !float_checkbounds(amb.i, 0, 1))
	{
		ft_putendl("Ambiant : out of bound value");
		return (0);
	}
	return (1);
}

int			parse_ambiant(t_scene *sce, char **t)
{
	t_f		color_normalize;

	if (!check_numeric(PARAM_AMBIANT, t))
	{
		ft_putendl("Wrong Ambiant format in scene file");
		return (0);
	}
	color_normalize = 1. / 255.;
	sce->ambiant.color.r = (t_f)ft_atoi(*t) * color_normalize;
	sce->ambiant.color.g = (t_f)ft_atoi(*(t + 1)) * color_normalize;
	sce->ambiant.color.b = (t_f)ft_atoi(*(t + 2)) * color_normalize;
	sce->ambiant.i = ft_atof(*(t + 3));
	return (check_ambiant(sce->ambiant));
}
