#include "renderer.h"

int	(*get_obj_intersection(enum e_object_type obj_type))(t_obj*, t_ray*)
{
	if (obj_type == CSG)
		return (&csg_intersect);
	if (obj_type == SPHERE)
		return (&sphere_intersect);
	if (obj_type == CYLINDER)
		return (&cylinder_intersect);
	if (obj_type == CONE)
		return (&polygon_intersect);//TODO ADD POLYGON OBJ
	if (obj_type == PLANE)
		return (&plane_intersect);
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
		return (&polygon_normal);
	if (obj_type == PLANE)
		return (&plane_normal);
	else
		return (NULL);
}

int	(*get_obj_intersection_csg(enum e_object_type obj_type))(t_obj*, t_ray*, t_interval*)
{
	if (obj_type == SPHERE)
		return (&sphere_intersect_csg);
	if (obj_type == CYLINDER)
		return (&cylinder_intersect_csg);
	else
		return (NULL);
}

t_vec3	(*get_obj_normal_csg(enum e_object_type obj_type))(t_obj*, t_vec3)
{
	if (obj_type == SPHERE)
		return (&sphere_normal_csg);
	if (obj_type == CYLINDER)
		return (&cylinder_normal_csg);
	else
		return (NULL);
}
