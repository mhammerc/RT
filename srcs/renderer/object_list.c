/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:19:10 by gpoblon           #+#    #+#             */
/*   Updated: 2017/04/24 16:19:11 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "renderer.h"
#include "shared.h"

t_list			*ft_lstdup(t_list *original_begin)
{
	t_list	*original;
	t_list	*original_cpy;
	t_list	*n;
	t_obj	*obj;
	t_face	*faces;

	n = NULL;
	original = original_begin;
	while (original)
	{
		original_cpy = ft_lstnew(original->content, original->content_size);
		obj = (t_obj*)original_cpy->content;
		if (obj->type == POLYGONS)
		{
			faces = monloc(sizeof(t_face) * obj->nb_faces);
			memcpy(faces, obj->faces, sizeof(t_face) * obj->nb_faces);
			obj->faces = faces;
		}
		ft_lstadd(&n, original_cpy);
		original = original->next;
	}
	return (n);
}

void			lstfree(t_list *begin)
{
	t_list	*list;
	t_list	*tmp;
	t_obj	*obj;

	list = begin;
	while (list)
	{
		obj = (t_obj*)list->content;
		if (obj->type == POLYGONS && obj->faces)
			free(obj->faces);
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}
