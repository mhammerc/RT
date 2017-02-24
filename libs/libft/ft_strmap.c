/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:09:41 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:09:57 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_s;
	size_t	i;

	IFNSETN(s);
	IFNSETN(f);
	new_s = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	IFNSETN(new_s);
	i = 0;
	while (s[i])
	{
		new_s[i] = f(s[i]);
		++i;
	}
	new_s[i] = '\0';
	return (new_s);
}
