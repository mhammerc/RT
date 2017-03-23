/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:56:43 by racousin          #+#    #+#             */
/*   Updated: 2017/03/23 10:09:01 by racousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "ui.h"
#include "converter.h"
#include "renderer.h"

void		convert_polygon(t_obj *obj, t_object *object)
{
	size_t			i;
	size_t			j;
	t_face			*face;
	t_vec3			*sommets;

	obj->length = fabs(obj->length);
	if (obj->length == 0)
		obj->length = 1;
	obj->faces = (t_face*)monloc(sizeof(t_face) * object->nb_faces);
	memcpy(obj->faces, object->faces, sizeof(t_face) * object->nb_faces);
	i = 0;
	while (i < obj->nb_faces)
	{
		face = obj->faces + i;
		j = 0;
		sommets = (t_vec3*)monloc(sizeof(t_vec3) * face->nb);
		while (j < face->nb)
		{
			sommets[j] = vec3_mult(obj->length, face->sommets[j]);
			sommets[j] = vec3_add(sommets[j], obj->pos);
			j++;
		}
		face->sommets = sommets;
		i++;
	}
}

void		convert_torus(t_obj *self)
{
	if (self->dir.x == 0 && self->dir.y == 0 && self->dir.z == 0)
		self->dir.z = 1;
	if (self->dir.x == 0)
		self->dir.x = 0.07;
	if (self->dir.y == 0)
		self->dir.y = 0.07;
	if (self->dir.z == 0)
		self->dir.z = 0.07;
	if (self->dir.x == 0)
		self->dir.x = 0.07;
	if (self->dir.y == 0)
		self->dir.y = 0.07;
	if (self->dir.z == 0)
		self->dir.z = 0.07;
	if (self->radius < 0.2)
		self->radius = 0.2;
	if (self->length < 0.1)
		self->length = 0.1;
	if (self->length > self->radius / 1.1)
		self->length = self->radius / 1.1;
}

void		convert_object2(t_obj *obj, t_object *object)
{
	if (vec3_norm2(object->rot) > EPS)
		obj->dir = vec3_get_normalized(object->rot);
	else
		obj->dir = object->rot;
	obj->length = object->length;
	obj->param = object->length / 1000;
	obj->type = object->type;
	obj->kspec = object->kspec;
	obj->kdiff = object->kdiff;
	obj->kp = 256;
	obj->rindex = object->rindex;
	obj->transmittance = object->transmittance;
	obj->reflectance = object->reflectance;
	obj->intersect = get_obj_intersection(obj->type);
	obj->normal = get_obj_normal(obj->type);
	obj->left = NULL;
	obj->right = NULL;
	obj->csg = '0';
	obj->nb_faces = object->nb_faces;
	obj->faces = object->faces;
	obj->have_texture = object->have_texture;
	obj->texture = object->texture;
}

void		convert_object(t_obj *obj, t_object *object, t_obj *parent)
{
	obj->pos = object->pos;
	obj->color = object->color;
	if (vec3_norm2(object->rot) > EPS)
		obj->dir = vec3_get_normalized(object->rot);
	else
		obj->dir = object->rot;
	if (object->type == CONE)
		obj->radius = cos(object->radius * DEG_TO_RAD);
	else
		obj->radius = object->radius / 1000;
	convert_object2(obj, object);
	apply_parent_relative(parent, obj);
	if (obj->type == POLYGONS)
		convert_polygon(obj, object);
	else if (obj->type == TORUS)
		convert_torus(obj);
}

void		convert_csg2(t_obj *renderer_obj, t_object *ui_root)
{
	renderer_obj->type = CSG;
	renderer_obj->intersect = get_obj_intersection(renderer_obj->type);
	renderer_obj->normal = get_obj_normal(renderer_obj->type);
	renderer_obj->left = (t_obj*)monloc(sizeof(t_obj));
	renderer_obj->right = (t_obj*)monloc(sizeof(t_obj));
	renderer_obj->csg = ui_root->operation;
	renderer_obj->pos = ui_root->pos;
	renderer_obj->color = ui_root->color;
	renderer_obj->dir = ui_root->rot;
	renderer_obj->radius = ui_root->radius;
	renderer_obj->length = ui_root->length;
	renderer_obj->param = ui_root->length / 1000;
}
