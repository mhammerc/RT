#include "renderer.h"

int	(*get_obj_intersection(enum e_object_type obj_type))(t_obj*, t_ray*, t_interval*)
{
	if (obj_type == CSG)
		return (&csg_intersect);
	if (obj_type == SPHERE)
		return (&sphere_intersect);
	if (obj_type == CYLINDER)
		return (&cylinder_intersect);
	if (obj_type == CONE)
		return (&cone_intersect);
	if (obj_type == PLANE)
		return (&plane_intersect);
	if (obj_type == DISK)
		return (&disk_intersect);
	if (obj_type == TORUS)
		return (&torus_intersect);
	if (obj_type == POLYGONS)
		return (&polygon_intersect);
	else
		return (NULL);
}

t_vec3	(*get_obj_normal(enum e_object_type obj_type))(t_obj*, t_vec3)
{
	if (obj_type == CSG)
		return (&csg_normal);
	if (obj_type == SPHERE)
		return (&sphere_normal);
	if (obj_type == CYLINDER)
		return (&cylinder_normal);
	if (obj_type == CONE)
		return (&cone_normal);
	if (obj_type == PLANE)
		return (&plane_normal);
	if (obj_type == DISK)
		return (&disk_normal);
	if (obj_type == TORUS)
		return (&torus_normal);
	if (obj_type == POLYGONS)
		return (&polygon_normal);
	else
		return (NULL);
}
