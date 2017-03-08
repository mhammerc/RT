#ifdef __APPLE__
# include <OpenCL/opencl.h>
#elif __linux__
# include <CL/cl.h>
#endif

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

void	vect3d_2_float3(FLOAT3 *vect_cl, t_vector3d vect_c)
{
	(*vect_cl).x = vect_c.x;
	(*vect_cl).y = vect_c.y;
	(*vect_cl).z = vect_c.z;
}

FLOAT3	vector3d_to_float3(t_vector3d v)
{
	FLOAT3	v2;

	v2.x = v.x;
	v2.y = v.y;
	v2.z = v.z;
	return (v2);
}
//TODO put vector3d flot3 operator in other file
t_vector3d	less(t_vector3d a, t_vector3d b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vector3d	add(t_vector3d a, t_vector3d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

FLOAT3	add_cl(FLOAT3 a, FLOAT3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

void	obj_c_2_cl(t_obj *obj, t_list *objs, t_obj *parent)
{
	t_object	objects;
	t_object	objects_parent;

	objects = *((t_object*)(objs->content));
	vect3d_2_float3(&((*obj).pos), objects.pos);
	vect3d_2_float3(&((*obj).color), objects.color);
	vect3d_2_float3(&((*obj).dir), objects.rot);
	(*obj).radius =  objects.radius;
	(*obj).length = objects.length;
	(*obj).param = objects.length / 1000;
	if (parent)
	{
		(*obj).pos = add_cl((*obj).pos, (*parent).pos);
		(*obj).param *= (*parent).param;
	}
}
void	spot_c_2_cl(t_spot *spot, t_list *objs, t_spot *parent)
{
	t_object	objects;
	t_object	objects_parent;

	objects = *((t_object*)(objs->content));
	vect3d_2_float3(&((*spot).pos), objects.pos);
	if (parent)
		((*spot).pos) = add_cl((*spot).pos, (*parent).pos);
}
		//need to optimise this shit !
void	fill_obj(t_list *objects, t_obj *obj, int *id, int	*parent)
{
	int	tmp;

	tmp = *id;
	if (objects && is_obj(objects))
	{
		if (*parent != -1)
			obj_c_2_cl(&(obj[*id]), objects, &(obj[*parent]));
		else
			obj_c_2_cl(&(obj[*id]), objects, 0);
		//obj[*id].param = 1;
		obj[*id].type = ((t_object*)(objects->content))->type;
		obj[*id].id = *id;
		obj[*id].kspec = 1;
		obj[*id].kdiff = 1;
		obj[*id].kp = 256;
		obj[*id].dir.x = 0;
		obj[*id].dir.y = 1;
		obj[*id].dir.x = 0;
		(*id)++;
	}
	if (objects->next)
	{
		fill_obj(objects->next, obj, id, parent);
	}
	if (objects->children)
	{
		*parent = tmp;
		fill_obj(objects->children, obj, id, parent);
	}
	//TODO for children is necessary to ajust the value with scale
}
//TODO for now, just one spot is effective and hierarchy spot obj doesn't work
void	fill_spot(t_list *objects, t_spot *spot, int *id, int *parent)
{
	int	tmp;

	tmp = *id;
	if (objects && is_light(objects))
	{
		if (*parent != -1)
			spot_c_2_cl(&(spot[*id]), objects, &(spot[*parent]));
		else
			spot_c_2_cl(&(spot[*id]), objects, 0);
		spot[*id].color.x = 1;
		spot[*id].color.y = 1;
		spot[*id].color.z = 1;
		spot[*id].intensity = 1;
		(*id)++;
		//spot[*id].id = *id; besoin d'un id?
	}
	if (objects->next)
	{
		fill_spot(objects->next, spot, id, parent);
	}
	if (objects->children)
	{
		*parent = tmp;
		fill_spot(objects->children, spot, id, parent);
	}
}

void	ask_for_new_image(t_ui *ui)
{
	t_obj	*obj;
	t_spot	*spot;
	int		nb_obj;
	int		nb_light;
	int		id;
	int		parent;


	nb_obj = 0;
	nb_light = 0;
	gtk_objects2nb_obj(ui->objs, &nb_obj, &nb_light);
	printf("nb_obj %d\n", nb_obj);

	obj = (t_obj*)malloc(sizeof(t_obj) * nb_obj);
	spot = (t_spot*)malloc(sizeof(t_spot) * (nb_light));
	if(!obj || !spot)
		exit(EXIT_FAILURE);

	id = 0;
	parent = -1;
	fill_obj(ui->objs, obj, &id, &parent);
	id = 0;
	parent = -1;
	spot[0].color.x = 1;
	spot[0].color.y = 1;
	spot[0].color.z = 1;
	spot[0].intensity = 1;
	spot[0].pos.x = 0;
	spot[0].pos.y = 1;
	spot[0].pos.z = 7;

	fill_spot(ui->objs, spot, &id, &parent);

	//sera modifier dynamiquement par la suite
	ui->scene.nb_obj = nb_obj;
	//ui->scene.cam = *(ui->cam);
	ui->scene.cam.dir = vector3d_to_float3(ui->cam->dir);
	ui->scene.cam.pos = vector3d_to_float3(ui->cam->pos);
	ui->scene.cam.w = RENDER_SIZE_W;
	ui->scene.cam.h = RENDER_SIZE_H;
	ui->scene.ambiant.intensity = 0.42;
	ui->scene.ambiant.color.x = 1.0;
	ui->scene.ambiant.color.y = 1.0;
	ui->scene.ambiant.color.z = 1.0;
	ui->scene.cam.up.x = 0.0;
	ui->scene.cam.up.y = 1.0;
	ui->scene.cam.up.z = 0.0;
	ui->scene.cam.fov = 45.0;
	ui->scene.cam.ratio = 1.0;
	ui->scene.nb_spot = 1;
	ui->scene.obj = obj;
	ui->scene.light = spot;

	ui_print_scene(renderer_compute_image((&(ui->scene))));
}
