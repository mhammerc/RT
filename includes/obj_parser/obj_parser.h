#ifndef OBJ_PARSER
# define OBJ_PARSER

# include "ui.h"

typedef struct		s_faces_components
{
	size_t			n_sommets;
	size_t			n_textures;
	size_t			n_normales;
	size_t			n_faces;
	t_vec3			*sommets;
	t_vec2			*textures;
	t_vec3			*normales;
}					t_faces_components;

t_object	*parse_wavefront_file(char *filename);

#endif
