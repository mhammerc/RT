/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 09:40:57 by racousin          #+#    #+#             */
/*   Updated: 2017/03/07 17:02:07 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_rx(t_obj *obj)
{
	double	tmp_y;
	double	tmp_z;

	tmp_y = obj->other.y * cos(obj->rx) - obj->other.z * sin(obj->rx);
	tmp_z = obj->other.y * sin(obj->rx) + obj->other.z * cos(obj->rx);
	obj->other.y = tmp_y;
	obj->other.z = tmp_z;
}

void		ft_ry(t_obj *obj)
{
	double	tmp_x;
	double	tmp_z;

	tmp_x = obj->other.x * cos(obj->ry) + obj->other.z * sin(obj->ry);
	tmp_z = -obj->other.x * sin(obj->ry) + obj->other.z * cos(obj->ry);
	obj->other.x = tmp_x;
	obj->other.z = tmp_z;
}

void		ft_rz(t_obj *obj)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = obj->other.x * cos(obj->rz) - obj->other.y * sin(obj->rz);
	tmp_y = obj->other.x * sin(obj->rz) + obj->other.y * cos(obj->rz);
	obj->other.x = tmp_x;
	obj->other.y = tmp_y;
}

void		ft_global_rot(t_obj *obj)
{
	ft_rx(obj);
	ft_ry(obj);
	ft_rz(obj);
}
