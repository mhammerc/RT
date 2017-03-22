/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_basic_objs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:36:01 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:39:46 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Create an object and set everything to zero.
** Automatically add it to the interface.
*/

void		create_light(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = LIGHT;
	object.operation = '0';
	object.pos.z = 7.;
	ft_strcpy(object.name, "Light");
	add_object(object, render_new);
}

void		create_sphere(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = SPHERE;
	object.color.z = 1;
	object.radius = 50;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Sphere");
	add_object(object, render_new);
}

void		create_plane(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = PLANE;
	object.color.z = 1;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Plane");
	add_object(object, render_new);
}

void		create_cone(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CONE;
	object.color.z = 1;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Cone");
	add_object(object, render_new);
}

void		create_cylinder(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CYLINDER;
	object.color.z = 1;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Cylinder");
	add_object(object, render_new);
}
