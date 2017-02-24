/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:09:19 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:09:28 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_s;
	unsigned int	i;

	IFNSETN(s);
	IFNSETN(f);
	new_s = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	IFNSETN(new_s);
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		++i;
	}
	new_s[i] = '\0';
	return (new_s);
}
