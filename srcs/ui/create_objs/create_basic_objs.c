/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_basic_objs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:36:01 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 18:54:25 by gpoblon          ###   ########.fr       */
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
	object.pos.z = 7.;
	object.length = 100.;
	object.color = (t_vec3){1., 1., 1.};
	ft_strcpy(object.name, "Light");
	add_object(object, render_new);
}

void		create_sphere(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = SPHERE;
	object.radius = 50;
	ft_strcpy(object.name, "Sphere");
	add_object(object, render_new);
}

void		create_plane(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = PLANE;
	object.rot.z = 1;
	ft_strcpy(object.name, "Plane");
	add_object(object, render_new);
}

void		create_cone(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CONE;
	object.rot.y = 1.;
	ft_strcpy(object.name, "Cone");
	add_object(object, render_new);
}

void		create_cylinder(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CYLINDER;
	object.rot.y = 1;
	ft_strcpy(object.name, "Cylinder");
	add_object(object, render_new);
}
