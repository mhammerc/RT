/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:39:12 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 14:12:08 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	found;

	if (ft_strlen(little) == 0)
		return (char*)(big);
	i = -1;
	found = 0;
	while (big[++i])
	{
		j = 0;
		found = 1;
		while (big[i + j] && little[j] && i + j < len)
		{
			if (big[i + j] != little[j])
			{
				found = 0;
				break ;
			}
			++j;
		}
		if (found && little[j] == '\0')
			return (&(((char*)(big))[i]));
	}
	return (NULL);
}
