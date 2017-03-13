# include "ui.h"

void		add_obj_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget		*popover;

	ui = (t_ui*)view;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover), ui->lp->lp_btns.add_obj);
	GtkWidget *submenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	GtkWidget *empty = gtk_button_new_with_label("Empty");
	GtkWidget *sphere = gtk_button_new_with_label("Sphere");
	GtkWidget *plane = gtk_button_new_with_label("Plane");
	GtkWidget *cylinder = gtk_button_new_with_label("Cylinder");
	GtkWidget *cone = gtk_button_new_with_label("Cone");
	GtkWidget *torus = gtk_button_new_with_label("Torus");
	GtkWidget *csg = gtk_button_new_with_label("CSG");
	GtkWidget *polygons = gtk_button_new_with_label("Polygons");
	g_signal_connect(sphere, "clicked", G_CALLBACK(create_sphere), NULL);
	g_signal_connect(plane, "clicked", G_CALLBACK(create_plane), NULL);
	g_signal_connect(cylinder, "clicked", G_CALLBACK(create_cylinder), NULL);
	g_signal_connect(cone, "clicked", G_CALLBACK(create_cone), NULL);
	g_signal_connect(torus, "clicked", G_CALLBACK(create_torus), NULL);
	g_signal_connect(csg, "clicked", G_CALLBACK(create_cgs), NULL);
	g_signal_connect(polygons, "clicked", G_CALLBACK(create_polygons), NULL);
	g_signal_connect(empty, "clicked", G_CALLBACK(create_empty), NULL);
	gtk_container_add(GTK_CONTAINER(submenu), sphere);
	gtk_container_add(GTK_CONTAINER(submenu), empty);
	gtk_container_add(GTK_CONTAINER(submenu), plane);
	gtk_container_add(GTK_CONTAINER(submenu), cylinder);
	gtk_container_add(GTK_CONTAINER(submenu), cone);
	gtk_container_add(GTK_CONTAINER(submenu), torus);
	gtk_container_add(GTK_CONTAINER(submenu), csg);
	gtk_container_add(GTK_CONTAINER(submenu), polygons);
	gtk_container_add(GTK_CONTAINER(popover), submenu);
	gtk_widget_show_all(popover);
}

void		add_light_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget		*popover;

	ui = (t_ui*)view;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover), ui->lp->lp_btns.add_light);
	GtkWidget *submenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	GtkWidget *light = gtk_button_new_with_label("Diffuse");
	g_signal_connect(light, "clicked", G_CALLBACK(create_light), NULL);
	gtk_container_add(GTK_CONTAINER(submenu), light);
	gtk_container_add(GTK_CONTAINER(popover), submenu);
	gtk_widget_show_all(popover);
}

void		ft_lst_cpy(t_list **new, t_list *original)
{
	ft_lstpushback(new, ft_lstnew(original->content, sizeof(t_object)));
	if (original->children)
		ft_lst_cpy(&((*new)->children), original->children);
	if (original->next)
		ft_lst_cpy(&((*new)->next), original->next);
}


void		cpy_obj_btn(GtkButton *button, gpointer data)
{
	t_list			*tmp;
	t_list			*new;
	t_ui			*ui;
	int				*index;
	int				depth;
	GtkTreePath		*path;
	t_object		*obj;

	ui = (t_ui*)data;
	index = ui->selected_obj.index;
	depth = ui->selected_obj.depth;
	new = NULL;
	if (ui->selected_obj.object)
	{
		path = gtk_tree_model_get_path(GTK_TREE_MODEL(ui->lp->tree.store),
				&ui->selected_obj.iter);
		obj = ui->selected_obj.object;
		tmp = ft_lstat_child(ui->objs, index, depth);
		ft_lstpushback(&new, ft_lstnew(tmp->content, sizeof(t_object)));
		if (tmp->children)
			ft_lst_cpy(&new->children, tmp->children);
		ft_lstpushback(&tmp, new);
		refresh_obj_tree(ui);
		gtk_tree_view_expand_to_path(GTK_TREE_VIEW(ui->lp->tree.tree), path);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(ui->lp->tree.tree), path, 0, 0);
		ui->selected_obj.object = obj;
		gtk_tree_model_get_iter(GTK_TREE_MODEL(ui->lp->tree.store),
				&ui->selected_obj.iter, path);
	}
}

static void	ui_free_object(t_object *object)
{
	size_t	i;

	if (object->filename)
		free(object->filename);
	if (object->faces)
	{
		i = 0;
		while (i < object->nb_faces)
		{
			free(object->faces[i].sommets);
			free(object->faces[i].normales);
			free(object->faces[i].textures);
			++i;
		}
		free(object->faces);
	}
	free(object);
}

void		del_obj_btn(GtkButton *button, gpointer data)
{
	t_list			*tmp;
	t_list			*tmp_clean;
	t_ui		*ui;
	int				*index;
	int				depth;

	ui = (t_ui*)data;
	index = ui->selected_obj.index;
	depth = ui->selected_obj.depth;
	if (ui->selected_obj.object)
	{
		if (index[depth - 1] == 0)
		{
			if (depth == 1)
			{
				tmp_clean = ui->objs;
				ui->objs = ui->objs->next;
				ui_free_object(tmp_clean->content);
				free(tmp_clean); //FIXME free content
			}
			else
			{
				tmp = ft_lstat_child(ui->objs, index, depth - 1);
				tmp_clean = tmp->children;
				tmp->children = tmp_clean->next;
				ui_free_object(tmp_clean->content);
				free(tmp_clean);//TODO free content et children
			}
		}
		else
		{
			tmp = ft_lstat_child_before(ui->objs, index, depth);
			tmp_clean = tmp->next;
			tmp->next = tmp_clean->next;
			ui_free_object(tmp_clean->content);
			free(tmp_clean);//TODO free content
		}
		refresh_obj_tree(ui);
	}
}
