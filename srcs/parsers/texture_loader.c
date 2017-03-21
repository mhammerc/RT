#include "texture_loader.h"
#include <libft.h>

t_texture	load_texture(char const *filename)
{
	t_texture	texture;

	texture.error = NULL;
	texture._pixbuf = gdk_pixbuf_new_from_file(filename, &texture.error);
	texture.is_valid = 0;
	if (!texture._pixbuf)
		return (texture);
	texture.pixels = gdk_pixbuf_get_pixels(texture._pixbuf);
	texture.width = gdk_pixbuf_get_width(texture._pixbuf);
	texture.height = gdk_pixbuf_get_height(texture._pixbuf);
	texture.rowstride = gdk_pixbuf_get_rowstride(texture._pixbuf);
	texture.bytes_per_pixel = gdk_pixbuf_get_byte_length(texture._pixbuf);
	texture.bits_per_color = gdk_pixbuf_get_bits_per_sample(texture._pixbuf);
	texture.has_alpha = gdk_pixbuf_get_has_alpha(texture._pixbuf);
	texture.is_valid = 1;
	return (texture);
}

void		free_texture(t_texture *texture)
{
	if (texture->is_valid)
	{
		g_object_unref(texture->_pixbuf);
		ft_bzero(texture, sizeof(t_texture));
	}
}
