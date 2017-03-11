#include <stdlib.h>
#include <libft.h>

#include "ui.h"
#include "renderer.h"

static int	is_obj(t_object *object)
{
	return (object->type < 5);
}

static int	is_light(t_object *object)
{
	return (object->type == LIGHT);
}

static void	convert_object(t_obj *obj, t_object *object, t_obj *parent)
{
	obj->pos = object->pos;
	obj->color = object->color;
	obj->dir = object->rot;
	obj->radius =  object->radius;
	obj->length = object->length;
	obj->param = object->length / 1000;
	obj->type = object->type;
	obj->kspec = 1;
	obj->kdiff = 1;
	obj->kp = 256;
	obj->dir = (t_vec3){0, 1, 0};
	obj->intersect = get_obj_intersection(obj->type);
	obj->normal = get_obj_normal(obj->type);
	obj->intersect_csg = get_obj_intersection_csg(obj->type);
	obj->normal_csg = get_obj_normal_csg(obj->type);
	obj->left = NULL;
	obj->right = NULL;
	obj->csg = '0';
	if (parent)
	{
		obj->pos = vec3_add(obj->pos, parent->pos);
		obj->param *= parent->param;
	}
	/*if (object->operation != '0' && objects->children)
	{
		left = (t_obj*)malloc(sizeof(t_obj));
		right = (t_obj*)malloc(sizeof(t_obj));
		*left = *obj;
		convert_object(right, objects->children, 0);
		obj->csg = object->operation;
		obj->left = left;
		obj->right = right;
	}*/
}

static int		convert_csg(t_obj *renderer_obj, t_list *objects)
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
	renderer_obj->color.x = 0xff;
	if (ui_son1->type != CSG)
		convert_object(renderer_obj->left, ui_son1, 0);
	else
	{
		if (!convert_csg(renderer_obj->left, objects->children))
			return (FALSE);
	}
	if (ui_son2->type != CSG)
		convert_object(renderer_obj->right, ui_son2, 0);
	else
	{
		if (!convert_csg(renderer_obj->right, objects->children->next))
			return (FALSE);
	}
	return (TRUE);
}

static void		fill_obj(t_list *objects, t_list **objs)
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
			convert_object(&obj, object, 0);
			ft_lstpushback(objs, ft_lstnew(&obj, sizeof(t_obj)));
		}

		if (object->type == CSG)
		{
			if (convert_csg(&obj, objects))
				ft_lstpushback(objs, ft_lstnew(&obj, sizeof(t_obj)));
		}
	}
	if (objects->next)
		fill_obj(objects->next, objs);
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
	del_list(&ui->scene.obj);
	del_list(&ui->scene.spot);
	fill_obj(ui->objs, &(ui->scene.obj));
	fill_spot(ui->objs, &(ui->scene.spot));

	//sera modifier dynamiquement par la suite
	//ui->scene.cam = *(ui->cam);
	ui->scene.cam.dir = ui->cam->dir;
	ui->scene.cam.pos = ui->cam->pos;
	ui->scene.cam.w = RENDER_SIZE_W;
	ui->scene.cam.h = RENDER_SIZE_H;
	ui->scene.ambiant.intensity = 0.42;
	ui->scene.ambiant.color = (t_vec3){1, 1, 1};
	ui->scene.cam.up = (t_vec3){0, 1, 0};
	ui->scene.cam.fov = 45.0;
	ui->scene.cam.ratio = 1.0;

	renderer_compute_image((&(ui->scene)));
}
