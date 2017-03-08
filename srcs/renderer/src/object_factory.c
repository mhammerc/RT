/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_factory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:22:21 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 13:53:57 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "rtv1.h"

/*
** Creates an object given a string from the scene file
** @return 1 if ok, 0 if fail
*/

int			object_factory(t_scene *sce, char **t)
{
	t_obj	*o;
	t_list	*e;

	if (0 == ft_strcmp("Sphere", *t))
		o = sphere_new(t + 1);
	else if (0 == ft_strcmp("Plane", *t))
		o = plane_new(t + 1);
	else if (0 == ft_strcmp("Disk", *t))
		o = disk_new(t + 1);
	else if (0 == ft_strcmp("Cone", *t))
		o = cone_new(t + 1);
	else if (0 == ft_strcmp("Cylinder", *t))
		o = cylinder_new(t + 1);
	else
		return (0);
	if (NULL == o || NULL == (e = ft_lstcreateelem(o, sizeof(t_obj))))
	{
		free(o);
		ft_putendl("Error while creating object from scene file");
		return (0);
	}
	ft_lstpushback(&(sce->obj), e);
	return (1);
}
