/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/02/25 23:20:44 by vfour            ###   ########.fr       */
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

typedef struct			s_color
{
	float				r;
	float				g;
	float				b;
}						t_color;

struct					s_ray
{
	FLOAT3				origine;
	FLOAT3				dir;
	FLOAT				t;
	FLOAT3				hit;
};
typedef struct s_ray	t_ray;

struct					s_cam
{
	FLOAT3				origine;
	FLOAT3				dir;
	FLOAT3				up;
	FLOAT3				vx;
	FLOAT3				vy;
	FLOAT3				top_left;
	FLOAT				fov;
	FLOAT				ratio;
};
typedef struct s_cam	t_cam;

struct					s_obj
{
	FLOAT3				origine;
	FLOAT3				dir;
	FLOAT				PARAM;
	INT					type;
	//the following should live in a material struct
	FLOAT3				color;
	float				kspec;
	float				kdiff;
	float				kp;
};
typedef struct s_obj	t_obj;

struct					s_spot
{
	FLOAT3				origine;
	FLOAT3				color;
	FLOAT				intensity;
};
typedef struct s_spot	t_spot;

struct					s_scene
{
	t_obj	*obj;
	INT		nb_obj;
	t_spot	*light;
	INT		nb_spot;
	t_spot	ambiant;
	t_cam	cam;
	INT		s_x;
	INT		s_y;
};
typedef struct s_scene	t_scene;

struct					s_cl_scene
{
	INT		nb_obj;
	INT		nb_spot;
	t_spot	ambiant;
	t_cam	cam;
	INT		s_x;
	INT		s_y;
};
typedef struct s_cl_scene	t_cl_scene;

#endif
