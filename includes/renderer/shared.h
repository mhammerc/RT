/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/03/22 20:47:08 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <libft.h>
# include <texture_loader.h>

# define DEG_TO_RAD M_PI / 180.0
# define RAD_TO_DEG 180.0 / M_PI
# define BIG_DIST 1e12
# define EPS 1e-3
# define INITIAL_RAY 0
# define OCCLUSION_RAY 1
# define REFLECTION_RAY 2
# define REFL_ATTENUATION 0.8
# define WHITE (t_vec3){1., 1., 1.}
# define BLACK (t_vec3){0., 0., 0.}
//# define REFR_ATTENUATION 0.8
# define MAX_REC_DEPTH 8
# define R_GLASS 1.42
# define R_DEFAULT 1.0
# define ABSORB_COEFF 0.15

typedef struct s_ui	t_ui;

enum e_object_type
{
	SPHERE,
	PLANE,
	DISK,
	CONE,
	CYLINDER,
	TORUS,
	CSG,
	POLYGONS,
	EMPTY,
	LIGHT,
	OBJECT_TYPE_COUNT
};

enum e_texture_type
{
	NO_TEXTURE,
	SPHERICAL,
	SPHERICAL_DAMIER,
	PLANAR,
	PLANAR_DAMIER,
	TEXTURE_TYPE_COUNT
};

enum e_filters
{
	NONE,
	BLACK_WHITE,
	SEPIA,
	FILTERS_COUNT
};

struct						s_vec3
{
	double					x;
	double					y;
	double					z;
};
typedef struct s_vec3		t_vec3;

typedef struct				s_vec2
{
	double					x;
	double					y;
}							t_vec2;


struct						s_cam
{
	t_vec3					pos;
	t_vec3					dir;
	t_vec3					up;
	t_vec3					vx;
	t_vec3					vy;
	t_vec3					top_left;
	double					fov;
	double					ratio;
	int						w;
	int						h;
};
typedef struct s_cam		t_cam;

typedef struct				s_face
{
	t_vec3					*sommets;
	t_vec3					*normales;
	t_vec2					*textures;
	double					aire;
	size_t					nb;
}							t_face;

typedef struct s_obj		t_obj;

typedef struct s_ray		t_ray;
typedef struct s_interval	t_interval;

struct						s_obj
{
	t_vec3					pos;
	t_vec3					dir;
	t_vec3					color;
	double					param;
	double					radius;
	double					length;
	enum e_object_type		type;
	int						id;
	int						transparency;
	double					kspec;
	double					kdiff;
	double					kp;
	double					rindex;
	double					transmittance;
	double					reflectance;
	struct s_obj			*left;
	struct s_obj			*right;
	char					csg;
	int						normal_dir;
	struct s_obj			*csg_ref;
	int						(*intersect)(struct s_obj *self, t_ray *ray, t_interval*);
	t_vec3					(*normal)(struct s_obj *self, t_vec3 pos);
	size_t					nb_faces;
	t_face					*faces;
	enum e_texture_type		have_texture;
	t_texture				texture;
};

struct						s_csg
{
	double					dist;
	int						normal;
	t_obj					ref;
};
typedef	struct s_csg		t_csg;

struct						s_interval
{
	t_csg					min[20];
	t_csg					max[20];
	int						nb_hit;
};

typedef struct		s_obj_stack
{
	t_obj			*obj[MAX_REC_DEPTH];
	int				size;
}					t_obj_stack;

struct						s_ray
{
	t_vec3					pos;
	t_vec3					dir;
	t_vec3					n;
	double					t;
	int						type;
	t_obj					*collided;
	t_vec3					light;
	t_obj_stack				rstack;
	int						location;
	double					dist;
};

struct						s_spot
{
	t_vec3					pos;
	t_vec3					color;
	double					intensity;
};
typedef struct s_spot		t_spot;

struct						s_scene
{
	t_list					*obj;
	t_list					*spot;
	t_spot					ambiant;
	t_cam					cam;
	t_ui					*ui;
	double					*percent;
	int						*pixels;
	int						aa;
	enum e_filters			filter;
};
typedef struct s_scene		t_scene;

int			minimal_positiv(t_interval *interval, t_obj *obj, double *d, t_obj **collided);

#endif
