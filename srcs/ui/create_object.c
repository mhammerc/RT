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

void		create_sphere(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = SPHERE;
	object.color.z = 1;
	object.operation = '0';
	ft_strcpy(object.name, "Sphere");
	add_object(object, render_new);
}

void		create_plane(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = PLANE;
	object.color.z = 1;
	object.operation = '0';
	ft_strcpy(object.name, "Plane");
	add_object(object, render_new);
}

void		create_cone(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CONE;
	object.color.z = 1;
	object.operation = '0';
	ft_strcpy(object.name, "Cone");
	add_object(object, render_new);
}

void		create_cylinder(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CYLINDER;
	object.color.z = 1;
	object.operation = '0';
	ft_strcpy(object.name, "Cylinder");
	add_object(object, render_new);
}

void		create_torus(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = TORUS;
	object.color.z = 1;
	object.operation = '0';
	ft_strcpy(object.name, "Torus");
	add_object(object, render_new);
}

void		create_cgs(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = CSG;
	object.operation = '0';
	ft_strcpy(object.name, "CSG");
	add_object(object, render_new);
}

void		create_polygons(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = POLYGONS;
	object.operation = '0';
	ft_strcpy(object.name, "Polygons");
	add_object(object, render_new);
}

void		create_empty(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = EMPTY;
	object.operation = '0';
	ft_strcpy(object.name, "Empty");
	add_object(object, render_new);
}

void		create_light(gboolean render_new)
{
	t_object	object;

	ft_bzero(&object, sizeof(t_object));
	object.type = LIGHT;
	object.operation = '0';
	ft_strcpy(object.name, "Light");
	add_object(object, render_new);
}
