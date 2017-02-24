/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/02/24 12:11:24 by racousin         ###   ########.fr       */
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

struct					s_ray
{
	FLOAT3	origine;
	FLOAT3	dir;
	FLOAT	t;
	FLOAT3	hit;
};
typedef struct s_ray	t_ray;

struct					s_cam
{
	FLOAT	origine;
	FLOAT	dir;
};
typedef struct s_cam	t_cam;

struct					s_obj
{
	FLOAT3	origine;
	INT		type;
	FLOAT	size;
	FLOAT3	dir;
	FLOAT	col;
};
typedef struct s_obj	t_obj;

struct					s_spot
{
	FLOAT3	origine;
};
typedef struct s_spot	t_spot;

struct					s_scene
{
	t_cam	cam;
	INT		s_x;
	INT		s_y;
	INT		nb_ray;
	INT		nb_spot;
	INT		nb_obj;
};
typedef struct s_scene	t_scene;

#endif
