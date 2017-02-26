/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/02/26 17:13:43 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# ifdef __APPLE__
#  define FLOAT3 cl_float3
#  define FLOAT cl_float
#  define INT cl_int
# else
#  define FLOAT3 float3
#  define FLOAT float
#  define INT int
# endif

# define DEG_TO_RAD M_PI / 180.0
# define RAD_TO_DEG 180.0 / M_PI
# define BIG_DIST 1e42
# define INITIAL_RAY 0
# define OCCLUSION_RAY 1
# define SPHERE 0

struct						s_ray
{
	FLOAT3					pos;
	FLOAT3					dir;
	FLOAT3					n;
	FLOAT					t;
	INT						type;
	INT						collided;
	FLOAT3					hit;
	FLOAT3					color;
};
typedef struct s_ray		t_ray;

struct						s_cam
{
	FLOAT3					pos;
	FLOAT3					dir;
	FLOAT3					up;
	FLOAT3					vx;
	FLOAT3					vy;
	FLOAT3					top_left;
	FLOAT					fov;
	FLOAT					ratio;
	INT						w;
	INT						h;
};
typedef struct s_cam		t_cam;

struct						s_obj
{
	FLOAT3					pos;
	FLOAT3					dir;
	FLOAT					param;
	INT						type;
	INT						id;
	//the following should live in a material struct
	FLOAT3					color;
	FLOAT					kspec;
	FLOAT					kdiff;
	FLOAT					kp;
};
typedef struct s_obj		t_obj;

struct						s_spot
{
	FLOAT3					pos;
	FLOAT3					color;
	FLOAT					intensity;
};
typedef struct s_spot		t_spot;

struct						s_scene
{
	t_obj					*obj;
	INT						nb_obj;
	t_spot					*light;
	INT						nb_spot;
	t_spot					ambiant;
	t_cam					cam;
	INT						s_x;
	INT						s_y;
};
typedef struct s_scene		t_scene;

struct						s_cl_scene
{
	INT						nb_obj;
	INT						nb_spot;
	FLOAT3					ambiant;
	t_cam					cam;
	INT						s_x;
	INT						s_y;
};
typedef struct s_cl_scene	t_cl_scene;

/*
** Vectors
*/
FLOAT						vec3_norm(FLOAT3 v);
void						vec3_normalize(FLOAT3 *v);
FLOAT3						vec3_get_normalized(FLOAT3 v);
FLOAT						vec3_norm2(FLOAT3 v);
FLOAT3						vec3_add(FLOAT3 a, FLOAT3 b);
FLOAT3						vec3_cross(FLOAT3 u, FLOAT3 v);
FLOAT						vec3_dot(FLOAT3 a, FLOAT3 b);
FLOAT3						vec3_mult(FLOAT m, FLOAT3 x);
FLOAT3						vec3_sub(FLOAT3 a, FLOAT3 b);

t_cam						camera_set(t_cam cam);

#endif
