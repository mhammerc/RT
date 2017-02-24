/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:06:50 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/04 10:36:19 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	long	divisor;
	long	n2;
	char	*result;
	size_t	i;

	result = (char*)malloc(sizeof(char) * 11);
	IFNSETN(result);
	n2 = (long)n;
	i = 0;
	if (n2 < 0)
	{
		result[i++] = '-';
		n2 = -n2;
	}
	divisor = 10;
	while (n2 / divisor != 0)
		divisor *= 10;
	divisor /= 10;
	while (divisor != 0)
	{
		result[i++] = n2 / divisor % 10 + 48;
		divisor /= 10;
	}
	result[i] = 0;
	return (result);
}
