/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 19:00:24 by lmarques          #+#    #+#             */
/*   Updated: 2017/03/10 18:28:24 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_entity_lst	*ft_new_entity(t_entity entity)
{
	t_entity_lst	*tmp;

	if (!(tmp = (t_entity_lst *)malloc(sizeof(t_entity_lst))))
		return (NULL);
	tmp->entity.type = entity.type;
	tmp->entity.obj.type = entity.obj.type;
	tmp->entity.obj.radius = entity.obj.radius;
	tmp->entity.obj.length = entity.obj.length;
	tmp->entity.obj.pos = entity.obj.pos;
	tmp->entity.obj.rot = entity.obj.rot;
	tmp->entity.obj.color = entity.obj.color;
	ft_strcpy(tmp->entity.obj.name, entity.obj.name);
	tmp->next = NULL;
	return (tmp);
}

void			ft_push_entity(t_entity_lst **entity_lst, t_entity_lst *new)
{
	t_entity_lst	*tmp;

	tmp = NULL;
	tmp = *entity_lst;
	if (!tmp)
		*entity_lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_group_lst		*ft_new_group(t_entity_lst *entity_lst)
{
	t_group_lst	*tmp;

	if (!(tmp = (t_group_lst *)malloc(sizeof(t_group_lst))))
		return (NULL);
	tmp->group = entity_lst;
	tmp->next = NULL;
	return (tmp);
}

void			ft_push_group(t_group_lst **group_lst, t_group_lst *new)
{
	t_group_lst	*tmp;

	tmp = NULL;
	tmp = *group_lst;
	if (!tmp)
		*group_lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
