/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:36:13 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 15:28:16 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest <= src)
	{
		i = 0;
		while (i < n - 1)
		{
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
			++i;
		}
	}
	else
	{
		i = n - 1;
		while (i > 0)
		{
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
			--i;
		}
	}
	((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
	return (dest);
}
