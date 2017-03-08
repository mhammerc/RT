/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 22:37:17 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:22:38 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

static int	check_light(t_light *l)
{
	if (!float_checkbounds(l->color.r, 0, 1)
		|| !float_checkbounds(l->color.g, 0, 1)
		|| !float_checkbounds(l->color.b, 0, 1)
		|| !float_checkbounds(l->i, 0, 1))
	{
		ft_putendl("Light : out of bound value");
		return (0);
	}
	return (1);
}

int			parse_light(t_scene *sce, char **t)
{
	t_list	*elem;
	t_light *light;

	if (!check_numeric(PARAM_LIGHT, t))
	{
		ft_putendl("Wrong Light format in scene file");
		return (0);
	}
	if (NULL == (light = light_new(t)))
		ft_exit("Light constructor failed", EXIT_FAILURE);
	if (NULL == (elem = ft_lstcreateelem(light, sizeof(t_light))))
		ft_exit("List elem malloc failed for light", EXIT_FAILURE);
	ft_lstpushback(&(sce->light), elem);
	return (check_light(light));
}
