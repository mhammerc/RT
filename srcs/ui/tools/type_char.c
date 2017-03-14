#include "ui.h"

char			*get_el_type_char(t_object *object)
{
	static char		*type[] = {"SPHERE", "PLANE", "CONE", "CYLINDER", "TORUS",
								"CSG", "POLYGONS", "EMPTY", "LIGHT", "\0", };

	return (type[object->type]);
}
