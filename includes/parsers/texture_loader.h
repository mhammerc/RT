/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:13:38 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/24 16:17:33 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_LOADER_H
# define TEXTURE_LOADER_H

# include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct		s_texture
{
	guchar			*pixels;
	int				width;
	int				height;
	int				bytes_per_pixel;
	int				rowstride;
	int				bits_per_color;
	gboolean		has_alpha;
	GdkPixbuf		*pixbuf;
	GError			*error;
	int				is_valid;
}					t_texture;

t_texture			load_texture(char const *filename);
void				free_texture(t_texture *texture);

#endif
