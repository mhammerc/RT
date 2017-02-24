/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:15:39 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:15:40 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i == 0 || s[i - 1])
	{
		if (s[i] == (char)c)
			return ((char*)(s) + sizeof(char) * i);
		++i;
	}
	return (NULL);
}
