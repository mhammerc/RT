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
#define ENV_H
struct					s_ray
{
	float3	origine;
	float3	dir;
	float	t;
	float3	hit;
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
	float3	origine;
	int		type;
	float	size;
	float	dir;
	float3	dir;
	float	col;
};
typedef struct s_obj	t_obj;

struct					s_spot
{
	float3	origine;
};
typedef struct s_spot	t_spot;

#endif
