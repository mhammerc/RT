/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:14:52 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:14:54 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "ui.h"
#include "renderer.h"
#include "converter.h"

int			is_obj(t_object *object)
{
	return (object->type < EMPTY);
}

int			is_light(t_object *object)
{
	return (object->type == LIGHT);
}

void		apply_parent_relative(t_obj *parent, t_obj *child)
{
	if (!parent)
		return ;
	child->pos = vec3_add(child->pos, parent->pos);
}

void		del_list(t_list **list)
{
	t_list	*object;
	t_list	*next;

	if (NULL == list)
		return ;
	object = *list;
	while (object)
	{
		next = object->next;
		free(object->content);
		free(object);
		object = next;
	}
	*list = NULL;
}

void		del_list_obj(t_list **list)
{
	t_list	*object;
	t_list	*next;
	t_obj	*obj;
	int		i;

	if (!list)
		return ;
	object = *list;
	while (object)
	{
		next = object->next;
		obj = (t_obj*)object->content;
		if (obj->type == POLYGONS)
		{
			i = -1;
			while ((size_t)++i < obj->nb_faces)
				free(obj->faces[i].sommets);
			free(obj->faces);
		}
		free(object->content);
		free(object);
		object = next;
	}
	*list = NULL;
}
