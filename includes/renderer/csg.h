/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:19:04 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/24 16:17:50 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H

# include <libft.h>
# include "shared.h"

int					csg_intersect(t_obj *self, t_ray *ray,
		t_interval *interval);
t_vec3				csg_normal(t_obj *self, t_vec3 pos);

int					norm_quad_solve2(double b, double c, t_interval *interval);
int					quad_solve2(double a, double b, double c,
		t_interval *interval);

typedef	int			(*t_intersect_f)(struct s_obj*, t_ray*, t_interval*);
typedef t_vec3		(*t_normal_f)(t_obj*, t_vec3);

t_intersect_f		get_obj_intersection(enum e_object_type type);
t_normal_f			get_obj_normal();

int					sphere_intersect_csg(t_obj *self, t_ray *ray,
		t_interval *interval);
t_vec3				sphere_normal_csg(t_obj *self, t_vec3 pos);
int					cylinder_intersect_csg(t_obj *obj, t_ray *ray,
		t_interval *interval);
t_vec3				cylinder_normal_csg(t_obj *obj, t_vec3 pos);
int					cone_intersect_csg(t_obj *self, t_ray *ray,
		t_interval *interval);
t_vec3				cone_normal_csg(t_obj *self, t_vec3 pos);
void				ft_union(t_interval *left, t_interval *right,
		t_interval *interval);
int					is_disjoint(t_interval *a_i, t_interval *a_j, int i, int j);
void				inter(t_interval *left, t_interval *right,
		t_interval *interval);
void				minus(t_interval *left, t_interval *right,
		t_interval *interval);
int					minimal_positiv(t_interval *interval,
		t_obj *obj, double *d, t_obj **collided);
int					minus_case(t_interval *left, t_interval *right,
		t_interval *interval);
int					minus_test0(t_interval *a_i, t_interval *a_j,
		int i, int j);
int					minus_test00(t_interval *a_i, t_interval *a_j,
		int i, int j);

#endif
