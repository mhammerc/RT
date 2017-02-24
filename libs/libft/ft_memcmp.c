/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:38:17 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:57:42 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	diff = 0;
	while (i < n)
	{
		diff = ((t_uchar*)s1)[i] - ((t_uchar*)s2)[i];
		if (diff != 0)
			return (diff);
		++i;
	}
	return (0);
}
