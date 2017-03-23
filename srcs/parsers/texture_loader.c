/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:37:44 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 10:37:45 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_loader.h"
#include <libft.h>

t_texture	load_texture(char const *filename)
{
	t_texture	texture;

	texture.error = NULL;
	texture.pixbuf = gdk_pixbuf_new_from_file(filename, &texture.error);
	texture.is_valid = 0;
	if (!texture.pixbuf)
		return (texture);
	texture.pixels = gdk_pixbuf_get_pixels(texture.pixbuf);
	texture.width = gdk_pixbuf_get_width(texture.pixbuf);
	texture.height = gdk_pixbuf_get_height(texture.pixbuf);
	texture.rowstride = gdk_pixbuf_get_rowstride(texture.pixbuf);
	texture.bytes_per_pixel = gdk_pixbuf_get_byte_length(texture.pixbuf);
	texture.bits_per_color = gdk_pixbuf_get_bits_per_sample(texture.pixbuf);
	texture.has_alpha = gdk_pixbuf_get_has_alpha(texture.pixbuf);
	texture.is_valid = 1;
	return (texture);
}

void		free_texture(t_texture *texture)
{
	if (texture->is_valid)
	{
		g_object_unref(texture->pixbuf);
		ft_bzero(texture, sizeof(t_texture));
	}
}
