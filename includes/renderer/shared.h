/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/03/09 10:12:47 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <libft.h>

# define DEG_TO_RAD M_PI / 180.0
# define RAD_TO_DEG 180.0 / M_PI
# define BIG_DIST 1e12
# define EPS 1e-4
# define INITIAL_RAY 0
# define OCCLUSION_RAY 1


enum e_object_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	EMPTY,
	LIGHT,
	OBJECT_TYPE_COUNT
};

struct						s_vec3
{
	double					x;
	double					y;
	double					z;
};
typedef struct s_vec3		t_vec3;


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

typedef struct s_ray		t_ray;
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
	double					kspec;
	double					kdiff;
	double					kp;
	struct s_obj			*left;
	struct s_obj			*right;
	char					csg;
	int						(*intersect)(struct s_obj *self, t_ray *ray);
	t_vec3					(*normal)(struct s_obj *self, t_vec3 pos);
	int						nb_sommet;//pour les polygones (triangles, carre, ....) il faudra allouer un tableau de vecteur contenant les sommets
	t_vec3					*sommet;
};
typedef struct s_obj		t_obj;

struct						s_ray
{
	t_vec3					pos;
	t_vec3					dir;
	t_vec3					n;
	double					t;
	int						type;
	t_obj					*collided;
	t_vec3					hit;
	t_vec3					light;
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
};
typedef struct s_scene		t_scene;

#endif
