#include <stdlib.h>
#include "ui.h"
#include "renderer.h"

//TODO CHOOSE LIGHT OR SPOT
int		is_obj(t_list	*objects)
{
	int	type;

	type = ((t_object*)(objects->content))->type;
	return (type < 4);
}

int		is_light(t_list	*objects)
{
	int	type;

	type = ((t_object*)(objects->content))->type;
	return (type == 5);
}

void	gtk_objects2nb_obj(t_list *objects, int	*nb_obj, int *nb_light)
{
	int	type;

	if (!objects)
		return;
	type = ((t_object*)(objects->content))->type;
	if (type < 4)
		(*nb_obj)++;
	else if (type == 5)
		(*nb_light)++;
	gtk_objects2nb_obj(objects->next, nb_obj, nb_light);
	gtk_objects2nb_obj(objects->children, nb_obj, nb_light);
}

void	obj_c_2_cl(t_obj *obj, t_list *objs, t_obj *parent)
{
	t_object	objects;
	t_object	objects_parent;

	objects = *((t_object*)(objs->content));
	(*obj).pos = objects.pos;
	(*obj).color = objects.color;
	(*obj).dir = objects.rot;
	(*obj).radius =  objects.radius;
	(*obj).length = objects.length;
	(*obj).param = objects.length / 1000;
	if (parent)
	{
		(*obj).pos = vec3_add((*obj).pos, (*parent).pos);
		(*obj).param *= (*parent).param;
	}
}
void	spot_c_2_cl(t_spot *spot, t_list *objs, t_spot *parent)
{
	t_object	objects;
	t_object	objects_parent;

	objects = *((t_object*)(objs->content));
	spot->pos = objects.pos;
	if (parent)
		((*spot).pos) = vec3_add((*spot).pos, (*parent).pos);
}
		//need to optimise this shit !
void	fill_obj(t_list *objects, t_list **objs)
{
	t_obj	*obj;

	if (objects && is_obj(objects))
	{
		if (NULL == (obj = (t_obj*)ft_memalloc(sizeof(t_obj))))
			exit(EXIT_FAILURE);
		obj_c_2_cl(obj, objects, 0);
		obj->type = ((t_object*)(objects->content))->type;
		obj->kspec = 1;
		obj->kdiff = 1;
		obj->kp = 256;
		obj->dir = (t_vec3){0, 1, 0};
		obj->intersection = get_obj_intersection(obj->type);
		obj->normal = get_obj_normal(obj->type);
		ft_lstpostadd(objs, obj);
	}
	if (objects->next)
		fill_obj(objects->next, objs);
	/*
	if (objects->children)
	{
		*parent = tmp;
		fill_obj(objects->children, obj, id, parent);
	}
	*/
	//TODO for children is necessary to ajust the value with scale
}
//TODO for now, just one spot is effective and hierarchy spot obj doesn't work
void	fill_spot(t_list *objects, t_list **spots)
{
	t_spot	*spot;

	if (objects && is_light(objects))
	{
		if (NULL == (spot = (t_spot*)ft_memalloc(sizeof(t_spot))))
			exit(EXIT_FAILURE);
		spot_c_2_cl(spot, objects, 0);
		spot->color = (t_vec3){1, 1, 1};
		spot->intensity = 1;
		ft_lstpostadd(spots, spot);
	}
	if (objects->next)
		fill_spot(objects->next, spots);
	/*
	if (objects->children)
	{
		*parent = tmp;
		fill_spot(objects->children, spot, id, parent);
	}
	*/
}

void	del_list(t_list **obj)
{
	t_list	*truc;
	t_list	*next;

	if (NULL == obj)
		return ;
	truc = *obj;
	while (truc)
	{
		next = truc->next;
		free(truc->content);
		free(truc);
		truc = next;
	}
	*obj = NULL;
}

void	ask_for_new_image(t_ui *ui)
{
	/*
	t_obj	*obj;
	t_spot	*spot;
	int		id;
	int		parent;
	int		nb_obj;
	int		nb_light;
	

	nb_obj = 0;
	nb_light = 0;
	gtk_objects2nb_obj(ui->objs, &nb_obj, &nb_light);
	*/

	/*
	obj = (t_obj*)malloc(sizeof(t_obj) * nb_obj);
	spot = (t_spot*)malloc(sizeof(t_spot) * (nb_light));
	if(!obj || !spot)
		exit(EXIT_FAILURE);
	id = 0;
	parent = -1;
	*/
	del_list(&(ui->scene.obj));
	del_list(&(ui->scene.light));
	fill_obj(ui->objs, &(ui->scene.obj));
	fill_spot(ui->objs, &(ui->scene.light));

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

	ui_print_scene(renderer_compute_image((&(ui->scene))));
}
