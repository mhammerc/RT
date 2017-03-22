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
t_vec3		vec3_mul(t_vec3 a, t_vec3 b);
t_vec3		vec3_apply(t_vec3 a, double (*f)(double x));

t_cam		camera_set(t_cam cam);

t_vec3		get_texture_color(t_ray ray);

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
int			quad4_solve(long double *a, t_interval *interval);
void		solve_interval(t_interval *interval, long double *r_g, long double *r_h);
int			quad2_solve(long double b, long double c, long double *root);
void		adapt_polygon2csg(t_interval *interval, t_csg t, int *cmp);

int			stack_push(t_obj_stack *stack, t_obj *obj);
t_obj		*stack_pop(t_obj_stack *stack);
t_obj		*stack_peak(t_obj_stack *stack);
t_obj_stack	stack_new(void);

t_ray		ray_new(t_vec3 pos, t_vec3 aim);
t_ray		ray_new_dir(t_ray ray, t_vec3 dir);
t_ray		reflected_ray(t_ray ray);
t_ray	refracted_ray(t_ray ray);

int			colorcomp_to_rgb(int r, int g, int b);
void		light_to_pixel(t_vec3 *light, int *px, int w, int h);
t_vec3		color_light_mix(t_vec3 obj_color, t_vec3 light_color, double coeff);
t_vec3		color_add_light(t_ray ray, t_spot *l, t_vec3 obj_cam, t_vec3 absorbance);
t_vec3		color_average(t_vec3 *aa, int size);

t_vec3		ray_trace(t_scene *sce, t_ray ray, int depth);
int			rt_object(t_scene *sce, t_ray *ray);
t_vec3		rt_shadow(t_scene *sce, t_ray ray);
t_vec3		rt_light(t_scene *sce, t_ray ray);
int			ray_object(t_obj *obj, t_ray *ray);

#endif
