/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:05:06 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/11 13:05:06 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat_child(t_list *list, int *index, int depth)
{
	int	i;
	int	j;

	i = 0;
	while (i < depth)
	{
		j = 0;
		while (list && j < index[i])
		{
			list = list->next;
			j++;
		}
		if (depth - i > 1)
			list = list->children;
		i++;
	}
	return (list);
}

t_list	*ft_lstat_child_before(t_list *list, int *index, int depth)
{
	int	i;
	int	j;
	int	before;

	i = 0;
	before = 0;
	while (i < depth)
	{
		if (depth - i <= 1)
			before = 1;
		j = 0;
		while (list && j < index[i] - before)
		{
			list = list->next;
			j++;
		}
		if (depth - i > 1)
			list = list->children;
		i++;
	}
	return (list);
}
