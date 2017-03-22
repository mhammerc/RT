/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_interface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:46:47 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 16:30:35 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_ui	*get_interface(void)
{
	static t_ui		*ui = NULL;

	if (ui == NULL)
	{
		ui = (t_ui*)malloc(sizeof(t_ui));
		ft_bzero(ui, sizeof(t_ui));
	}
	return (ui);
}
