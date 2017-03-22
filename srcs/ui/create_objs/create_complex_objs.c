/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_complex_objs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:38:11 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 23:31:58 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Create an object and set everything to zero.
** Automatically add it to the interface.
*/

void		create_empty(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = EMPTY;
	ft_strcpy(object.name, "Empty");
	add_object(object, render_new);
}

void		create_disk(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = DISK;
	object.radius = 50;
	object.rot.z = 1;
	ft_strcpy(object.name, "Disk");
	add_object(object, render_new);
}

void		create_torus(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = TORUS;
	ft_strcpy(object.name, "Torus");
	add_object(object, render_new);
}

void		create_csg(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CSG;
	ft_strcpy(object.name, "CSG");
	add_object(object, render_new);
}

void		create_polygons(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = POLYGONS;
	ft_strcpy(object.name, "Polygons");
	add_object(object, render_new);
}
