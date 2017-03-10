#include "renderer.h"

int	(*get_obj_intersection(enum e_object_type obj_type))(t_obj*, t_ray*)
{
	if (obj_type == CSG)
		return (&csg_intersect);
	if (obj_type == SPHERE)
		return (&sphere_intersect);
	else
		return (NULL);
}

t_vec3	(*get_obj_normal(enum e_object_type obj_type))(t_obj*, t_vec3)
{
	if (obj_type == CSG)
		return (&csg_normal);
	if (obj_type == SPHERE)
		return (&sphere_normal);
	else
		return (NULL);
}
