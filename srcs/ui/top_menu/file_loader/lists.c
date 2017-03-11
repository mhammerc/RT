#include "ui.h"

t_entity_lst	*ft_new_entity(t_entity entity)
{
	t_entity_lst	*tmp;

	if (!(tmp = (t_entity_lst *)malloc(sizeof(t_entity_lst))))
		return (NULL);
	tmp->entity.type = entity.type;
	tmp->entity.type = entity.type;
	tmp->entity.radius = entity.radius;
	tmp->entity.length = entity.length;
	tmp->entity.pos = entity.pos;
	tmp->entity.rot = entity.rot;
	tmp->entity.color = entity.color;
	ft_strcpy(tmp->entity.name, entity.name);
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
