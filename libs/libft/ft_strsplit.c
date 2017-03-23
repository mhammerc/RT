/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:40:35 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/04 11:30:34 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

static int		count_parts(char const *s, char c)
{
	size_t	i;
	int		parts;

	i = 0;
	parts = 0;
	if (s[i] && s[i] != c)
		parts = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				++i;
			if (s[i])
				++parts;
			continue;
		}
		++i;
	}
	return (parts);
}

static void		copy_parts(char **arr, char const *s, char c)
{
	int			part;
	char const	*i;

	part = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (!*s)
			return ;
		i = s;
		while (*s && *s != c)
			++s;
		arr[part] = (char*)monloc(sizeof(char) * (s - i + 1));
		ft_strncpy(arr[part], i, s - i);
		arr[part][s - i] = 0;
		++part;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	int		parts;
	char	**arr;

	IFNSETN(s);
	parts = count_parts(s, c);
	arr = (char**)monloc(sizeof(char*) * (parts + 1));
	IFNSETN(arr);
	copy_parts(arr, s, c);
	arr[parts] = 0;
	return (arr);
}
