/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:38:11 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:38:18 by gpoblon          ###   ########.fr       */
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

	ft_bzero(&object, sizeof(t_object));
	object.type = EMPTY;
	object.operation = '0';
	ft_strcpy(object.name, "Empty");
	add_object(object, render_new);
}

void		create_disk(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = DISK;
	object.color.z = 1;
	object.radius = 50;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Disk");
	add_object(object, render_new);
}

void		create_torus(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = TORUS;
	object.color.z = 1;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Torus");
	add_object(object, render_new);
}

void		create_cgs(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CSG;
	object.operation = '0';
	ft_strcpy(object.name, "CSG");
	add_object(object, render_new);
}

void		create_polygons(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = POLYGONS;
	object.color.z = 1;
	object.operation = '0';
	object.kdiff = 1.;
	object.kspec = 1.;
	ft_strcpy(object.name, "Polygons");
	add_object(object, render_new);
}
