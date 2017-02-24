/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpostadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:04:29 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:04:45 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpostadd(t_list **alst, t_list *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	new->next = (*alst)->next;
	(*alst)->next = new;
}
