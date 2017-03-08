/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 22:23:35 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 16:17:44 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	check_camera(t_cam cam)
{
	if (cam.fov <= 0 || cam.fov > MAX_FOV || cam.ratio <= 0)
	{
		ft_putendl("Camera : out of bound value");
		return (0);
	}
	return (1);
}

int			parse_camera(t_scene *sce, char **t, int w, int h)
{
	if (!check_numeric(PARAM_CAMERA, t))
	{
		ft_putendl("Wrong Camera format in scene file");
		return (0);
	}
	if (NULL != sce->cam)
	{
		ft_putendl("Scene can not have more than one camera");
		return (0);
	}
	if (NULL == (sce->cam = camera_new(t, w, h)))
	{
		ft_putendl("Error while instanciating new camera");
		return (0);
	}
	return (check_camera(*(sce->cam)));
}
