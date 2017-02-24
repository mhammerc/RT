/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:15:47 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:15:48 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int n)
{
	long	i;
	long	j;
	long	mid;
	long	nb_fat;

	nb_fat = n;
	i = nb_fat;
	j = 0;
	while (j < i)
	{
		mid = (i + j) / 2;
		if (mid * mid < nb_fat)
			j = mid + 1;
		else
			i = mid;
	}
	return (i);
}
