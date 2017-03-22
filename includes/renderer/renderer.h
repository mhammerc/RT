#ifndef SCENE_MANAGER_H
# define SCENE_MANAGER_H

# include <libft.h>
# include <pthread.h>

# include "shared.h"
# include "csg.h"

# define CORE_COUNT 4

# define ALPHA_BITSHIFT 24
# define R_BITSHIFT 0
# define G_BITSHIFT 8
# define B_BITSHIFT 16
# define MAX_REC_DEPTH 42

# define OUTWARDS 0
# define INWARDS 1

# define LOCATION_NONE 0
# define LOCATION_INSIDE -1
# define LOCATION_OUTSIDE 1

typedef struct		s_renderer_thread
{
	t_scene			*sce;
	t_vec3			*light;
	int				*pixels;
	int				y_begin;
	int				y_end;
	int				y_range;
}					t_renderer_thread;


void		renderer_compute_image();

void		redraw_scene();

/*
** Vectors
*/
double		vec3_norm(t_vec3 v);
void		vec3_normalize(t_vec3 *v);
t_vec3		vec3_get_normalized(t_vec3 v);
double		vec3_norm2(t_vec3 v);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 u, t_vec3 v);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult(double m, t_vec3 x);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);

t_cam		camera_set(t_cam cam);

int			sphere_intersect(t_obj *self, t_ray *ray, t_interval *interval);
int			polygon_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		polygon_normal(t_obj *self, t_vec3 pos);
t_vec3		sphere_normal(t_obj *self, t_vec3 pos);
int			cylinder_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		cylinder_normal(t_obj *self, t_vec3 pos);
int			cone_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		cone_normal(t_obj *self, t_vec3 pos);
int			plane_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		plane_normal(t_obj *self, t_vec3 pos);
int			disk_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		disk_normal(t_obj *self, t_vec3 pos);
int			torus_intersect(t_obj *self, t_ray *ray, t_interval *interval);
t_vec3		torus_normal(t_obj *self, t_vec3 pos);

int (*get_obj_intersection(enum e_object_type))(t_obj*, t_ray*, t_interval*);
t_vec3 (*get_obj_normal())(t_obj*, t_vec3);

int			norm_quad_solve(double b, double c, t_interval *interval);
int			quad_solve(double a, double b, double c, t_interval *interval);
int			quad4_solve(long double a, long double b, long double c,
										long double d, t_interval *interval);
void		solve_interval(t_interval *interval, long double *r_g, long double *r_h);
int			quad2_solve(long double b, long double c, long double *root);

#endif
