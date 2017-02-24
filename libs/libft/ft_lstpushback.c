/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:04:16 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:04:17 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*iter;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	iter = *alst;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}
