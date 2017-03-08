/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:12:39 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/08 13:33:59 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_fd(const char *message, int fd)
{
	if (fd == 2)
	{
		if (message != NULL)
			ft_printf("\n\033[31m%s\033[0m\n", message);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (message != NULL)
			ft_printf("\n\033[36m%s\033[0m\n", message);
		exit(EXIT_SUCCESS);
	}
}
