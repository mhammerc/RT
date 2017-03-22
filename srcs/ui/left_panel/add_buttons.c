/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:01:22 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/22 16:49:59 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ui.h"

static void	create_btn(GtkWidget *parent, char *label, void (*f)(gboolean))
{
	GtkWidget	*btn;

	btn = gtk_button_new_with_label(label);
	g_signal_connect(btn, "clicked", G_CALLBACK(f), NULL);
	gtk_container_add(GTK_CONTAINER(parent), btn);
}

void		add_obj_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget	*popover;
	GtkWidget	*submenu;

	ui = (t_ui*)view;
	(void)button;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover), ui->lp->lp_btns.add_obj);
	submenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	create_btn(submenu, "Sphere", create_sphere);
	create_btn(submenu, "Empty", create_empty);
	create_btn(submenu, "Plane", create_plane);
	create_btn(submenu, "Disk", create_disk);
	create_btn(submenu, "Cylinder", create_cylinder);
	create_btn(submenu, "Cone", create_cone);
	create_btn(submenu, "Torus", create_torus);
	create_btn(submenu, "CSG", create_cgs);
	create_btn(submenu, "Polygons", create_polygons);
	gtk_container_add(GTK_CONTAINER(popover), submenu);
	gtk_widget_show_all(popover);
}

void		add_light_btn(GtkButton *button, gpointer view)
{
	t_ui		*ui;
	GtkWidget		*popover;

	ui = (t_ui*)view;
	(void)button;
	popover = gtk_popover_menu_new();
	gtk_popover_set_relative_to(GTK_POPOVER(popover),
		ui->lp->lp_btns.add_light);
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

static void	cpy_obj_btn_2(t_ui *ui, GtkTreePath *path, t_object *obj)
{
	refresh_obj_tree(ui);
	gtk_tree_view_expand_to_path(GTK_TREE_VIEW(ui->lp->tree.tree), path);
	gtk_tree_view_set_cursor(GTK_TREE_VIEW(ui->lp->tree.tree), path, 0, 0);
	ui->selected_obj.object = obj;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(ui->lp->tree.store),
		&ui->selected_obj.iter, path);
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
	(void)button;
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
		cpy_obj_btn_2(ui, path, obj);
	}
}

static void	ui_free_object(t_object *object)
{
	size_t	i;

	if (object->filename)
		g_free(object->filename);
	if (object->texture_filename)
		g_free(object->texture_filename);
	free_texture(&object->texture);
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

static void	ui_free_list_object(t_list	*objects)
{
	t_object	*object;

	object = objects->content;
	ui_free_object(object);
	if (objects->children)
		ui_free_list_object(objects->children);
	/*
	** Don't free next because we want to free that specific node
	*/
	free(objects);
}

void		del_obj_btn(GtkButton *button, gpointer data)
{
	t_list			*tmp;
	t_list			*tmp_clean;
	t_ui			*ui;
	int				*index;
	int				depth;

	ui = (t_ui*)data;
	(void)button;
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
				ui_free_list_object(tmp_clean);
			}
			else
			{
				tmp = ft_lstat_child(ui->objs, index, depth - 1);
				tmp_clean = tmp->children;
				tmp->children = tmp_clean->next;
				ui_free_list_object(tmp_clean);
			}
		}
		else
		{
			tmp = ft_lstat_child_before(ui->objs, index, depth);
			tmp_clean = tmp->next;
			tmp->next = tmp_clean->next;
			ui_free_list_object(tmp_clean);
		}
		refresh_obj_tree(ui);
		clear_properties_list(ui);
	}
}
