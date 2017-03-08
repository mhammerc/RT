#include "shared.h"

int(*) (struct obj*, t_ray*)	get_obj_intersection(enum e_object_type obj_type)
{
	if (obj_type == SPHERE)
		return (&sphere_intersect);
	else
		return (NULL);
}

t_vec3(*) (struct obj*, t_vec3)	get_obj_normal(enum e_object_type obj_type)
{
	if (obj_type == SPHERE)
		return (&sphere_normal);
	else
		return (NULL);
}
