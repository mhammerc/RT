/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <racousin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:48:25 by racousin          #+#    #+#             */
/*   Updated: 2017/04/24 16:00:52 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <math.h>
#include "ui.h"
#include "converter.h"
#include "renderer.h"

static int		convert_csg(t_obj *renderer_obj, t_list *objects, t_obj *parent)
{
	t_object	*ui_root;
	t_object	*ui_son1;
	t_object	*ui_son2;

	if (ft_lstcount(objects->children) != 2)
		return (FALSE);
	ui_root = (t_object*)objects->content;
	ui_son1 = (t_object*)objects->children->content;
	ui_son2 = (t_object*)objects->children->next->content;
	if (ui_root->operation == '0')
		return (FALSE);
	convert_csg2(renderer_obj, ui_root);
	apply_parent_relative(parent, renderer_obj);
	if (ui_son1->type > POLYGONS || ui_son2->type > POLYGONS)
		return (FALSE);
	if (ui_son1->type != CSG)
		convert_object(renderer_obj->left, ui_son1, renderer_obj);
	else if (!convert_csg(renderer_obj->left, objects->children, renderer_obj))
		return (FALSE);
	if (ui_son2->type != CSG)
		convert_object(renderer_obj->right, ui_son2, renderer_obj);
	else if (!convert_csg(renderer_obj->right, objects->children->next,
				renderer_obj))
		return (FALSE);
	return (TRUE);
}

static void		fill_obj(t_list *objects, t_list **objs, t_obj *parent)
{
	t_obj		obj;
	t_object	*object;

	if (!objects)
		return ;
	object = (t_object*)objects->content;
	ft_bzero(&obj, sizeof(t_obj));
	if (is_obj(object))
	{
		if (object->type != CSG)
		{
			convert_object(&obj, object, parent);
			ft_lstpushback(objs, ft_lstnew(&obj, sizeof(t_obj)));
		}
		if (object->type == CSG)
		{
			if (convert_csg(&obj, objects, parent))
				ft_lstpushback(objs, ft_lstnew(&obj, sizeof(t_obj)));
		}
	}
	if (objects->children && object->type != CSG)
		fill_obj(objects->children, objs, &obj);
	if (objects->next)
		fill_obj(objects->next, objs, parent);
}

static void		fill_spot(t_list *objects, t_list **spots)
{
	t_object	*object;
	t_spot		spot;

	if (!objects)
		return ;
	object = (t_object*)objects->content;
	if (is_light(object))
	{
		spot.pos = object->pos;
		spot.color = object->color;
		spot.intensity = object->length;
		spot.radius = object->radius;
		if (get_interface()->scene.filter == CARTOON)
		{
			spot.intensity = 30.;
			spot.radius = 0.;
		}
		if (spot.radius > 5.)
			spot.radius = 5.;
		ft_lstpushback(spots, ft_lstnew(&spot, sizeof(t_spot)));
	}
	if (objects->children)
		fill_spot(objects->children, spots);
	if (objects->next)
		fill_spot(objects->next, spots);
}

void			ask_for_new_image(t_ui *ui)
{
	if (ui->rendering == 1)
		return ;
	ui->scene.filter = ui->rp->scene_gtk.filter;
	del_list_obj(&ui->scene.obj);
	del_list(&ui->scene.spot);
	fill_obj(ui->objs, &(ui->scene.obj), NULL);
	fill_spot(ui->objs, &(ui->scene.spot));
	ui->scene.cam.dir = ui->cam->dir;
	ui->scene.cam.pos = ui->cam->pos;
	ui->scene.cam.up = ui->cam->up;
	ui->scene.cam.w = RENDER_SIZE_W;
	ui->scene.cam.h = RENDER_SIZE_H;
	ui->scene.ambiant.intensity = ui->rp->scene_gtk.ambiant_light;
	if (ui->scene.filter == CARTOON)
		ui->scene.ambiant.intensity = 5.;
	ui->scene.cam.fov = ui->rp->scene_gtk.fov;
	ui->scene.ambiant.color = (t_vec3){1, 1, 1};
	ui->scene.cam.ratio = 1.0;
	ui->scene.ui = ui;
	ui->scene.stereo = CAM_NORMAL;
	if (ui->scene.filter == STEREOSCOPIC)
		ui->scene.stereo = CAM_LEFT;
	ui->scene.aa = ui->rp->scene_gtk.aa * 2;
	ui->scene.aa = ui->scene.aa == 6 ? 8 : ui->scene.aa;
	renderer_compute_image((&(ui->scene)));
}
