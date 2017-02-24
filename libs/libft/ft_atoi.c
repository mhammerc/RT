/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 18:03:00 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 13:55:56 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char const *nptr)
{
	int			result;
	int			i;
	signed char	reverse;

	result = 0;
	i = 0;
	reverse = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\v' || nptr[i] == '\r' || nptr[i] == '\f')
		++i;
	if (nptr[i] == '-')
		reverse = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		++i;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += (int)(nptr[i] - 48);
		++i;
	}
	return (result * reverse);
}
