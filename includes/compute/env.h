/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/03/04 19:02:16 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# ifdef __APPLE__
#  include <OpenCL/OpenCL.h>
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
	FLOAT3					color;
	FLOAT					param;
	enum e_object_type		type;
	INT						id;
	FLOAT					kspec;
	FLOAT					kdiff;
	FLOAT					kp;
	INT						padding;
};
//6 * 4 bytes + 3 * 12 bytes = 24 + 36 = 60 bytes
//4 bytes of padding => 64 bytes
typedef struct s_obj		t_obj;

struct						s_spot
{
	FLOAT3					pos;
	FLOAT3					color;
	FLOAT					intensity;
	INT						padding;
};
//2 * 12 bytes + 4 bytes = 24 + 4 = 28 bytes
//4 bytes of padding => 32 bytes
typedef struct s_spot		t_spot;

struct						s_scene
{
	t_obj					*obj;
	INT						nb_obj;
	t_spot					*light;
	INT						nb_spot;
	t_spot					ambiant;
	t_cam					cam;
};
typedef struct s_scene		t_scene;

struct						s_cl_scene
{
	INT						nb_obj;
	INT						nb_spot;
	t_spot					ambiant;
	t_cam					cam;
};
typedef struct s_cl_scene	t_cl_scene;

#endif
