/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:24:54 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 13:57:12 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_space_local(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*s2;

	IFNSETN(s);
	i = 0;
	while (s[i] && is_space_local(s[i]))
		++i;
	start = i;
	end = ft_strlen(s);
	while (s[i])
	{
		if (!is_space_local(s[i]))
			end = i;
		++i;
	}
	s2 = (char*)malloc(sizeof(char) * (ft_strlen(s) - (ft_strlen(s) - end)
				- start + 1));
	IFNSETN(s2);
	i = start - 1;
	while (++i <= end)
		s2[i - start] = s[i];
	s2[i - start] = '\0';
	return (s2);
}
