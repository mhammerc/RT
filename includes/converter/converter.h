/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:01:42 by racousin          #+#    #+#             */
/*   Updated: 2017/03/23 10:09:24 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

# include "ui.h"

void		ask_for_new_image(t_ui *ui);
int			is_obj(t_object *object);
int			is_light(t_object *object);
void		apply_parent_relative(t_obj *parent, t_obj *child);
void		del_list(t_list **list);
void		del_list_obj(t_list **list);
void		convert_polygon(t_obj *obj, t_object *object);
void		convert_torus(t_obj *self);
void		convert_object2(t_obj *obj, t_object *object);
void		convert_object(t_obj *obj, t_object *object, t_obj *parent);
void		convert_csg2(t_obj *renderer_obj, t_object *ui_root);

#endif
