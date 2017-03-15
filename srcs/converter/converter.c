#include <stdlib.h>
#include <libft.h>

#include "ui.h"
#include "renderer.h"

static int	is_obj(t_object *object)
{
	return (object->type < 7);
}

static int	is_light(t_object *object)
{
	return (object->type == LIGHT);
}

static void	apply_parent_relative(t_obj *parent, t_obj *child)
{
	if (!parent)
		return ;
	child->pos = vec3_add(child->pos, parent->pos);
}

static void	convert_object(t_obj *obj, t_object *object, t_obj *parent)
{
	obj->pos = object->pos;
	obj->color = object->color;
	obj->dir = object->rot;
	obj->radius =  object->radius / 1000;
	obj->length = object->length;
	obj->param = object->length / 1000;
	obj->type = object->type;
	obj->kspec = object->kspec;
	obj->kdiff = object->kdiff;
	obj->kp = 256;
	obj->intersect = get_obj_intersection(obj->type);
	obj->normal = get_obj_normal(obj->type);
	obj->intersect_csg = get_obj_intersection_csg(obj->type);
	obj->normal_csg = get_obj_normal_csg(obj->type);
	obj->left = NULL;
	obj->right = NULL;
	obj->csg = '0';
	obj->nb_faces = object->nb_faces;
	obj->faces = object->faces;
	apply_parent_relative(parent, obj);
}

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
	renderer_obj->type = CSG;
	renderer_obj->intersect = get_obj_intersection(renderer_obj->type);
	renderer_obj->normal = get_obj_normal(renderer_obj->type);
	renderer_obj->left = (t_obj*)malloc(sizeof(t_obj));
	renderer_obj->right = (t_obj*)malloc(sizeof(t_obj));
	renderer_obj->csg = ui_root->operation;

	renderer_obj->pos = ui_root->pos;
	renderer_obj->color = ui_root->color;
	renderer_obj->dir = ui_root->rot;
	renderer_obj->radius =  ui_root->radius;
	renderer_obj->length = ui_root->length;
	renderer_obj->param = ui_root->length / 1000;
	apply_parent_relative(parent, renderer_obj);

	if (ui_son1->type != CSG)
		convert_object(renderer_obj->left, ui_son1, renderer_obj);
	else
	{
		if (!convert_csg(renderer_obj->left, objects->children, renderer_obj))
			return (FALSE);
	}
	if (ui_son2->type != CSG)
		convert_object(renderer_obj->right, ui_son2, renderer_obj);
	else
	{
		if (!convert_csg(renderer_obj->right, objects->children->next, renderer_obj))
			return (FALSE);
	}
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

//TODO for now, just one spot is effective and hierarchy spot obj doesn't work
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
		spot.color = (t_vec3){1, 1, 1};
		spot.intensity = 1;
		ft_lstpushback(spots, ft_lstnew(&spot, sizeof(t_spot)));
	}
	if (objects->next)
		fill_spot(objects->next, spots);
}

static void		del_list(t_list **list)
{
	t_list	*object;
	t_list	*next;

	if (NULL == list)
		return ;
	object = *list;
	while (object)
	{
		next = object->next;
		free(object->content);
		free(object);
		object = next;
	}
	*list = NULL;
}

void	ask_for_new_image(t_ui *ui)
{
	if (ui->rendering == 1)
		return ;
	del_list(&ui->scene.obj);
	del_list(&ui->scene.spot);
	fill_obj(ui->objs, &(ui->scene.obj), NULL);
	fill_spot(ui->objs, &(ui->scene.spot));

	ui->scene.cam.dir = ui->cam->dir;
	ui->scene.cam.pos = ui->cam->pos;
	ui->scene.cam.w = RENDER_SIZE_W;
	ui->scene.cam.h = RENDER_SIZE_H;
	ui->scene.ambiant.intensity = ui->rp->scene_gtk.ambiant_light;
	ui->scene.cam.fov = ui->rp->scene_gtk.fov;
	ui->scene.ambiant.color = (t_vec3){1, 1, 1};
	ui->scene.cam.ratio = 1.0;
	ui->scene.ui = ui;
	/*
	** aa = 1 = 2x2 = 1x2
	** aa = 2 = 4x4 = 2x2
	** aa = 3 = 8x8 = 8 (3x2 = 6)
	*/
	ui->scene.aa = ui->rp->scene_gtk.aa * 2;
	if (ui->scene.aa == 6)
		ui->scene.aa = 8;

	//FIXME camera up ne doit pas etre en dur ?
	ui->scene.cam.up = (t_vec3){0, 1, 0};

	renderer_compute_image((&(ui->scene)));
}
