/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:21:51 by vfour             #+#    #+#             */
/*   Updated: 2017/03/23 17:21:54 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			*monloc(size_t size)
{
	void		*truc;

	if (NULL == (truc = malloc(size)))
		exit(EXIT_FAILURE);
	return (truc);
}
