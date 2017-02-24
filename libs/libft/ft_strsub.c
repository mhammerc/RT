/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:40:05 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/02 18:40:26 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	IFNSETN(s);
	s2 = (char*)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s[start + i];
		++i;
	}
	s2[i] = '\0';
	return (s2);
}
