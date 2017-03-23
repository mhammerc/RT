/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:37:35 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 10:37:36 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"

t_object	*parse_wavefront_file(char *filename)
{
	static t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = POLYGONS;
	ft_strcpy(object.name, get_el_type_char(&object));
	object.operation = '0';
	if (!start_parsing(&object, filename))
		return (FALSE);
	return (&object);
}
