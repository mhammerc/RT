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

void	obj_c_2_cl(t_obj *obj, t_object object)
{
	vect3d_2_float3(&((*obj).pos), object.pos);
	//vect3d_2_float3(&((*obj).dir), object.rot);
	//add other parameters to modify
}
void	fill_obj(t_list *objects, t_obj *obj)
{

	int	i;
	t_object *ui_obj;

	i = 0;
	while (objects)
	{
		ui_obj = (t_object*)objects->content;
		obj_c_2_cl(obj + i, *((t_object*)(objects->content)));
		obj->radius = ui_obj->radius;
		obj->length = ui_obj->length;
		obj[i].color.x = 1;
		obj[i].color.y = 1;
		obj[i].color.z = 0;
		obj[i].param = 1;
		obj[i].type = ui_obj->type;
		obj[i].id = i;
		obj[i].kspec = 1;
		obj[i].kdiff = 1;
		obj[i].kp = 256;
		objects = objects->next;
		++i;
	}
	//TODO for children is necessary to ajust the value with scale
	//	if (objects->children)
	//		fill_obj(objects->children, ++obj);

}

void	ask_for_new_image(t_ui *ui)
{
	t_obj	*obj;
	t_spot	spot;
	int		nb_obj;

	//sera modifier dynamiquement par la suite
	spot.pos.x = 1;
	spot.pos.y = 4;
	spot.pos.z = 4;
	spot.color.x = 1;
	spot.color.y = 1;
	spot.color.z = 1;
	spot.intensity = 1;
	spot.pos.x = -1;
	spot.pos.y = 4;
	spot.pos.z = 4;
	spot.color.x = 1;
	spot.color.y = 1;
	spot.color.z = 1;
	spot.intensity = 1;

	nb_obj = gtk_objects2nb_obj(ui->objs);
	obj = (t_obj*)malloc(sizeof(t_obj) * nb_obj);
	if(!obj)
		exit(EXIT_FAILURE);
	fill_obj(ui->objs, obj);
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
