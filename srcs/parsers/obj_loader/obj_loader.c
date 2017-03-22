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
