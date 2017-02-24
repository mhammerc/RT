/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:06:18 by mhammerc          #+#    #+#             */
/*   Updated: 2016/12/06 16:39:37 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - dest_len - 1))
	{
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
