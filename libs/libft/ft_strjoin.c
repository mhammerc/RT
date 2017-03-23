/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:10:53 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:11:18 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	IFNSETN(s1);
	IFNSETN(s2);
	s3 = (char*)monloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	IFNSETN(s3);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		++j;
	}
	s3[i + j] = '\0';
	return (s3);
}
