#ifndef CSG_H
# define CSG_H

#include <libft.h>

struct				s_csg
{
	double	dist;
	int	normal;
	t_obj	*ref_normal;
	//typeobj
	//couleur
	//normal
};
typedef	struct s_csg		t_csg;
struct				s_interval
{
	t_csg	min[10];
	t_csg	max[10];
	int	nb_hit;
};
typedef struct s_interval	t_interval;
int				csg_intersect(t_obj *self, t_ray *ray);
t_vec3				csg_normal(t_obj *self, t_vec3 pos);
int				norm_quad_solve2(double b, double c, t_interval *interval);

#endif
