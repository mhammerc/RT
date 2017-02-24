/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:16:43 by mhammerc          #+#    #+#             */
/*   Updated: 2016/11/04 10:31:35 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	divisor;
	long	n2;

	n2 = (long)n;
	if (n2 < 0)
	{
		ft_putchar_fd('-', fd);
		n2 = -n2;
	}
	if (n2 == 0 || n2 == 1)
	{
		ft_putchar_fd(n2 + 48, fd);
		return ;
	}
	divisor = 1;
	while (n2 / divisor != 0)
		divisor *= 10;
	divisor /= 10;
	while (divisor != 0)
	{
		ft_putchar_fd(n2 / divisor % 10 + 48, fd);
		divisor /= 10;
	}
}
