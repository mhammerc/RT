//#include "env.h"

# include <OpenCL/opencl.h>
#include "ui.h"

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
}
void	fill_obj(t_list *objects, t_obj *obj)
{
	if(!objects)
		return;
	obj_c_2_cl(obj, *((t_object*)(objects->content)));
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
	spot.pos.x = 0;
	spot.pos.y = 0;
	spot.pos.z = 0;
	nb_obj = gtk_objects2nb_obj(ui->objs);
	obj = (t_obj*)malloc(sizeof(t_obj) * nb_obj);
	if(!obj)
		exit(EXIT_FAILURE);
	fill_obj(ui->objs, obj);
	ui->scene.nb_obj = nb_obj;
	ui->scene.nb_spot = 1;
	ui->scene.obj = obj;
	ui->scene.light = &spot;
	int i = 0;
	while (i < nb_obj)
	{
		printf("position obj x %f y %f z %f\n", (obj[i]).pos.x, (obj[i]).pos.y, (obj[i]).pos.z);
		i++;
	}
}
