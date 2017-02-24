/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 11:01:09 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/21 11:01:11 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*ns;

	len = ft_strlen(s);
	len = (len > n ? n : len);
	ns = (char*)malloc(sizeof(char) * (len + 1));
	IFNSETN(ns);
	ft_memcpy((void*)ns, (void*)s, len);
	ns[len] = 0;
	return (ns);
}
