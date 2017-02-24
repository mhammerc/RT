/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:10:26 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:10:49 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ns;

	len = ft_strlen(s);
	ns = (char*)malloc(sizeof(char) * (len + 1));
	IFNSETN(ns);
	ft_memcpy((void*)ns, (void*)s, len + 1);
	return (ns);
}
