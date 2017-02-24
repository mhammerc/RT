/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:36:47 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:36:48 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->next = NULL;
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
		return (list);
	}
	list->content_size = content_size;
	list->content = (void*)malloc(content_size);
	if (!list->content)
	{
		free(list);
		return (NULL);
	}
	ft_memcpy(list->content, (void*)content, content_size);
	return (list);
}
