/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:46:31 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:46:39 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	IFNSET(alst);
	IFNSET(*alst);
	IFNSET(del);
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
