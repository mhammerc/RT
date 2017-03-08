/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:36:37 by vfour             #+#    #+#             */
/*   Updated: 2017/03/08 15:12:23 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

static int		rt_object(t_scene *sce, t_ray *ray)
{
	t_list		*l;
	int			collision;

	l = sce->obj;
	collision = 0;
	while (l)
	{
		if (L_OBJ->intersect(L_OBJ, ray))
			collision = 1;
		l = l->next;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->pos = vec3_add(ray->pos, vec3_mult(ray->d - EPS, ray->dir));
		ray->n = ray->collided->normal(ray->collided, ray->pos);
	}
	return (collision);
}

/*
** Cast a ray to all lights in scene, add in light contribution
** @return nothing
*/

static void		rt_light(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_vec3		obj_cam;

	obj_cam = vec3_mult(-1, ray.dir);
	color_add_ambiant(ray.col, ray.collided->color, sce->ambiant);
	ray.type = OCCLUSION_RAY;
	l = sce->light;
	while (l)
	{
		ray.dir = vec3_sub(L_LIGHT->pos, ray.pos);
		ray.d = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.d, ray.dir);
		if (!rt_object(sce, &ray))
			color_add_light(ray, L_LIGHT, obj_cam);
		l = l->next;
	}
}

/*
** Cast all rays to compute all light contributions
** @return nothing
*/

void			rt(t_env *e)
{
	int			i;
	int			j;
	t_ray		r;
	t_vec3		aim;
	t_vec3		start;

	aim = e->sce->cam->top_left;
	r = ray_new_aim(e->sce->cam->pos, aim, e->color);
	i = -1;
	while (++i < e->h)
	{
		start = aim;
		j = -1;
		while (++j < e->w)
		{
			if (rt_object(e->sce, &r))
				rt_light(e->sce, r);
			aim = vec3_add(aim, e->sce->cam->vx);
			r = ray_new_aim(e->sce->cam->pos, aim, r.col + 1);
		}
		aim = vec3_sub(start, e->sce->cam->vy);
		r = ray_new_aim(e->sce->cam->pos, aim, r.col);
	}
}
