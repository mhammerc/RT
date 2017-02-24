/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:07:00 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:08:01 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	IFNSETZ(s1);
	IFNSETZ(s2);
	i = 0;
	while (i != n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	if (i != n && s1[i] != s2[i])
		return (0);
	return (1);
}
