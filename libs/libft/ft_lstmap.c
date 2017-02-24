/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 16:42:03 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/06 16:44:50 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *ret;
	t_list *tmp;
	t_list *bgn;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	if (!tmp || !(ret = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	bgn = ret;
	while (lst->next)
	{
		tmp = f(lst->next);
		if (tmp && (ret->next = ft_lstnew(tmp->content, tmp->content_size)))
		{
			ret = ret->next;
			lst = lst->next;
		}
		else
			lst->next = NULL;
	}
	return (bgn);
}
