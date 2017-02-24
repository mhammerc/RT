/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:44:15 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:56:48 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_uchar*)dest)[i] = ((t_uchar*)src)[i];
		if (((t_uchar*)dest)[i] == ((t_uchar)c))
			break ;
		++i;
	}
	if (i == n)
		return (NULL);
	return (dest + i + 1);
}
