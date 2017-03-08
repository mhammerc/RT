/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:11:32 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 14:05:42 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parse_object(t_scene *sce, char **t)
{
	int	param;

	param = 0;
	if (0 == ft_strcmp("Sphere", *t))
		param = PARAM_SPHERE;
	else if (0 == ft_strcmp("Plane", *t))
		param = PARAM_PLANE;
	else if (0 == ft_strcmp("Disk", *t))
		param = PARAM_DISK;
	else if (0 == ft_strcmp("Cone", *t))
		param = PARAM_CONE;
	else if (0 == ft_strcmp("Cylinder", *t))
		param = PARAM_CYLINDER;
	else
	{
		ft_putendl("Unknown object in scene file");
		return (0);
	}
	if (!check_numeric(param, t + 1))
	{
		ft_putstr("Wrong format for Object ");
		ft_putendl(*t);
		return (0);
	}
	return (object_factory(sce, t));
}
