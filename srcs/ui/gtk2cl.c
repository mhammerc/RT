//#include "env.h"

#ifdef __APPLE__
# include <OpenCL/opencl.h>
#elif __linux__
# include <CL/cl.h>
#endif

#include "ui.h"

int				*opencl_compute_image(t_scene *sce);
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

void	obj_c_2_cl(t_obj *obj, t_object object)
{
	vect3d_2_float3(&((*obj).pos), object.pos);
	//add other parameters to modify
}
void	fill_obj(t_list *objects, t_obj *obj)
{
	if(!objects)
		return;
	obj_c_2_cl(obj, *((t_object*)(objects->content)));
	(*obj).color.x = 1;
	(*obj).color.y = 1;
	(*obj).color.z = 0;
	(*obj).param = 1;
	(*obj).type = SPHERE; // ICI OMG
	(*obj).id = 0;
	(*obj).kspec = 1;
	(*obj).kdiff = 1;
	(*obj).kp = 256;
	if (objects->next)
		fill_obj(objects->next, obj + 1);
//TODO for children is necessary to ajust the value with scale
//	if (objects->children)
//		fill_obj(objects->children, ++obj);
}

void	init_gtk2cl(t_ui *ui)
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
	ui->scene.cam = *(ui->cam);
	ui->scene.cam.w = 800;
	ui->scene.cam.h = 600;
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
	opencl_compute_image((&(ui->scene)));

}
