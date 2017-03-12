/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:11:10 by racousin          #+#    #+#             */
/*   Updated: 2017/03/11 18:16:58 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Intersection between ray and polygon
** @return the distance between camera and object if there is collision
** or a negative value otherwise
*/


void		cube_constructor(t_obj *self, t_ray)
{
}
int				cube_intersect(t_obj *self, t_ray *ray)
{
	t_vec3		x;
	double		a;

t_vec3			cube_normal(t_obj *self, t_vec3 pos)
{
	if (vec3_dot(vec3_sub(pos, self->pos), self->dir) > 0)
		return (self->dir);
	return (vec3_mult(-1, self->dir));
}

