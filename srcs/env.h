/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:35:18 by racousin          #+#    #+#             */
/*   Updated: 2017/02/24 11:35:31 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# ifdef __APPLE__
#  define FLOAT3 cl_float3
# else
#  define FLOAT3 float3
# endif

struct					s_ray
{
	FLOAT3	origine;
	FLOAT3	dir;
	float	t;
	FLOAT3	hit;
};
typedef struct s_ray	t_ray;

struct					s_cam
{
	float	origine;
	float	dir;
};
typedef struct s_cam	t_cam;

struct					s_obj
{
	FLOAT3	origine;
	int		type;
	float	size;
	FLOAT3	dir;
	float	col;
};
typedef struct s_obj	t_obj;

struct					s_spot
{
	FLOAT3	origine;
};
typedef struct s_spot	t_spot;

#endif
