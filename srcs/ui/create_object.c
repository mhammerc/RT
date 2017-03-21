#include "ui.h"

/*
** Add the object `object` to the scene.
** This function may be called from outside.
** This is why it use get_interface().
*/

void		add_object(t_object object, gboolean render_new)
{
	t_ui		*ui;
	t_list		*lst;
	GtkTreeIter	elem;
	GtkTreeIter *father;

	ui = get_interface();
	if (!ui->selected_obj.object)
	{
		ft_lstpushback(&ui->objs, ft_lstnew(&object, sizeof(t_object)));
		if (render_new)
			refresh_obj_tree(ui);
	}
	else
	{
		father = &ui->selected_obj.iter;
		lst = ft_lstat_child(ui->objs, ui->selected_obj.index,
			ui->selected_obj.depth);
		ft_lstpushback(&lst->children, ft_lstnew(&object, sizeof(t_object)));
		gtk_tree_store_append(ui->lp->tree.store, &elem, father);
		gtk_tree_store_set(ui->lp->tree.store, &elem, 0, object.name, 1,
			get_el_type_char(&object), -1);
		gtk_tree_view_expand_row(GTK_TREE_VIEW(ui->lp->tree.tree),
			gtk_tree_model_get_path(GTK_TREE_MODEL(ui->lp->tree.store), father),
			FALSE);
		//refresh_obj_tree(ui);
	}
}

/*
** Create an object and set everything to zero.
** Automatically add it to the interface.
*/

t_object	create_base_object()
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.color.z = 1;
	object.type = EMPTY;
	//object.rindex = R_DEFAULT;
	object.rindex = 0.1;
	object.transmittance = 0;
	object.reflectance = 1;
	object.kdiff = 1.;
	object.kspec = 1.;
	object.operation = '0';
	return (object);
}

void		create_sphere(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = SPHERE;
	object.radius = 50;
	ft_strcpy(object.name, "Sphere");
	add_object(object, render_new);
}

void		create_plane(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = PLANE;
	object.rot.z = 1;
	ft_strcpy(object.name, "Plane");
	add_object(object, render_new);
}

void		create_disk(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = DISK;
	object.radius = 50;
	object.rot.z = 1;
	ft_strcpy(object.name, "Disk");
	add_object(object, render_new);
}

void		create_cone(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CONE;
	object.rot.y = 1.;
	ft_strcpy(object.name, "Cone");
	add_object(object, render_new);
}

void		create_cylinder(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CYLINDER;
	object.rot.y = 1;
	ft_strcpy(object.name, "Cylinder");
	add_object(object, render_new);
}

void		create_torus(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = TORUS;
	ft_strcpy(object.name, "Torus");
	add_object(object, render_new);
}

void		create_cgs(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = CSG;
	ft_strcpy(object.name, "CSG");
	add_object(object, render_new);
}

void		create_polygons(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = POLYGONS;
	ft_strcpy(object.name, "Polygons");
	add_object(object, render_new);
}

void		create_empty(gboolean render_new)
{
	t_object	object;

	object = create_base_object();
	object.type = EMPTY;
	ft_strcpy(object.name, "Empty");
	add_object(object, render_new);
}

void		create_light(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = LIGHT;
	object.pos.z = 7.;
	object.length = 100.;
	object.color = (t_vec3){1., 1., 1.};
	ft_strcpy(object.name, "Light");
	add_object(object, render_new);
}
