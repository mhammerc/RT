/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:05:26 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:05:27 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

char			*get_el_type_char(t_object *object)
{
	static char		*type[] = {"SPHERE", "PLANE", "DISK", "CONE", "CYLINDER",
						"TORUS", "CSG", "POLYGONS", "EMPTY", "LIGHT", "\0", };

	return (type[object->type]);
}
