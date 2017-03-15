#ifndef CSG_H
# define CSG_H

# include <libft.h>
# include "shared.h"

int				csg_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3				csg_normal(t_obj *self, t_vec3 pos);
int				norm_quad_solve2(double b, double c, t_interval *interval);
int				quad_solve2(double a, double b, double c, t_interval *interval);

int				(*get_obj_intersection_csg(enum e_object_type obj_type))(t_obj*, t_ray*, t_interval *);
t_vec3				(*get_obj_normal_csg(enum e_object_type obj_type))(t_obj*, t_vec3);

int				sphere_intersect_csg(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3				sphere_normal_csg(t_obj *self, t_vec3 pos);
int				cylinder_intersect_csg(t_obj *obj, t_ray *ray, t_interval *interval);
t_vec3				cylinder_normal_csg(t_obj *obj, t_vec3 pos);
int			cone_intersect_csg(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3			cone_normal_csg(t_obj *self, t_vec3 pos);

#endif
