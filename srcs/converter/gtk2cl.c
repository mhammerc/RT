#ifdef __APPLE__
# include <OpenCL/opencl.h>
#elif __linux__
# include <CL/cl.h>
#endif

#include "ui.h"
#include "renderer.h"

int		gtk_objects2nb_obj(t_list *objects)
{
	//TODO ne pas compter les obj empty
	if(!objects)
		return (0);
	return (1 + gtk_objects2nb_obj(objects->next) + gtk_objects2nb_obj(objects->children));
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
//pur vector3d flot3 operato in other file
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
	if (parent)
		((*obj).pos) = add_cl((*obj).pos, (*parent).pos);
}
void	fill_obj(t_list *objects, t_obj *obj, int *id, int	*parent)
{
	int	tmp;

	tmp = *id;
	if (objects)
	{
		if (*parent != -1)
			obj_c_2_cl(&(obj[*id]), objects, &(obj[*parent]));
		else
			obj_c_2_cl(&(obj[*id]), objects, 0);
		//need to optimise this triple if !
		obj[*id].param = 1;
		obj[*id].type = SPHERE; // ICI OMG
		obj[*id].id = *id;
		obj[*id].kspec = 1;
		obj[*id].kdiff = 1;
		obj[*id].kp = 256;
	}
	if (objects->next)
	{
		(*id)++;
		fill_obj(objects->next, obj, id, parent);
	}
	if (objects->children)
	{
		*parent = tmp;
		(*id)++;
		fill_obj(objects->children, obj, id, parent);
	}
	//TODO for children is necessary to ajust the value with scale
}

void	ask_for_new_image(t_ui *ui)
{
	t_obj	*obj;
	t_spot	spot;
	int		nb_obj;
	int		id;
	int		parent;

	//sera modifier dynamiquement par la suite
	spot.color.x = 1;
	spot.color.y = 1;
	spot.color.z = 1;
	spot.intensity = 1;
	spot.pos.x = 0;
	spot.pos.y = 1;
	spot.pos.z = 7;
	spot.color.x = 1;
	spot.color.y = 1;
	spot.color.z = 1;
	spot.intensity = 1;

	nb_obj = gtk_objects2nb_obj(ui->objs);
	obj = (t_obj*)malloc(sizeof(t_obj) * nb_obj);
	if(!obj)
		exit(EXIT_FAILURE);
	id = 0;
	parent = -1;
	fill_obj(ui->objs, obj, &id, &parent);
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
	ui->scene.light = &spot;
	ui_print_scene(renderer_compute_image((&(ui->scene))));
}
