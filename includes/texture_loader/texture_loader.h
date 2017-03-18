#ifndef TEXTURE_LOADER_H
# define TEXTURE_LOADER_H

# include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct		s_texture
{
	guchar			*pixels;
	int				width;
	int				height;
	/* Total number of byte (!!) */
	int				bytes_per_pixel;
	/* Number of bytes per row */
	int				rowstride;
	int				bits_per_color;
	gboolean		has_alpha;
	GdkPixbuf		*_pixbuf;
	GError			*error;
}					t_texture;

t_texture			load_texture(char const *filename);
void				free_texture(t_texture texture);

#endif
