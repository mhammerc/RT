/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbinary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:35:21 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/03 10:35:34 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbinary(size_t const size, void const *const ptr)
{
	unsigned char	*b;
	unsigned char	byte;
	int				i;
	int				j;

	IFNSET(ptr);
	b = (unsigned char*)ptr;
	i = size - 1;
	while (i >= 0)
	{
		j = 7;
		while (j >= 0)
		{
			byte = (b[i] >> j) & 1;
			ft_putnbr(byte);
			--j;
		}
		--i;
	}
}
