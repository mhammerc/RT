#include "ui.h"
#include "converter.h"

static void		object_name_edited(GtkWidget *emitter, gchar *new_text, gpointer data)
{
	t_object	*obj;
	t_ui	*ui;
	GtkTreePath *path;
	GtkTreeViewColumn *focus_column;

	ui = get_interface();
	obj = ui->selected_obj.object;
	ft_strcpy(obj->name, new_text);
	gtk_tree_store_set(GTK_TREE_STORE(ui->lp->tree.store), &ui->selected_obj.iter, 0, obj->name, -1);
}

static void		element_edited()
{
	t_object	*obj;
	t_ui	*ui;

	ui = get_interface();
	obj = ui->selected_obj.object;
	obj->pos.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.x)));
	obj->pos.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.y)));
	obj->pos.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.z)));

	obj->rot.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.x)));
	obj->rot.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.y)));
	obj->rot.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.z)));

	obj->radius = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.radius)));
	obj->length = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.length)));
	ask_for_new_image(ui);
	--ui->lock;
}

static char		get_operation_code_from_id(int id)
{
	if (id == 1)
		return ('I');
	if (id == 2)
		return ('U');
	if (id == 3)
		return ('-');
	return ('0');
}

static int		get_operation_id_from_code(char code)
{
	if (code == 'I')
		return (1);
	if (code == 'U')
		return (2);
	if (code == '-')
		return (3);
	return (0);
}

static void		bounding_edited(GtkComboBox *widget, gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	ui->selected_obj.object->operation = get_operation_code_from_id(gtk_combo_box_get_active(GTK_COMBO_BOX(widget)));
	ask_for_new_image(ui);
}

void			clear_properties_list(t_ui *ui)
{
	GList	*children;
	GList	*iter;

	children = gtk_container_get_children(GTK_CONTAINER(ui->rp->el_prop_lst));
	iter = children;
	while (iter != NULL)
	{
		gtk_widget_destroy(GTK_WIDGET(iter->data));
		iter = g_list_next(iter);
	}
	g_list_free(children);
}

void		 	edit_element_properties(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer data)
{
	t_ui		*view;
	t_list		*obj_lst;
	int			*tmp;

	printf("HERE\n");
	view = (t_ui*)data;
	tmp = gtk_tree_path_get_indices_with_depth(path, &(view->selected_obj.depth));
	ft_memcpy(view->selected_obj.index, tmp , 4 * (view->selected_obj.depth));
	int i = 0;
	while (i < view->selected_obj.depth)
	{
		printf("depth %d index %d\n", view->selected_obj.depth, *(view->selected_obj.index + i));
		i++;
	}
	printf("\n");
	obj_lst = ft_lstat_child(view->objs, view->selected_obj.index, view->selected_obj.depth);
	view->selected_obj.object = (t_object*)obj_lst->content;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(view->lp->tree.store), &view->selected_obj.iter, path);

	clear_properties_list(view);

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), gtk_label_new_with_mnemonic("_Element Properties"));
	GtkWidget	*name = create_text_entry("Name	", view->selected_obj.object->name);
	g_signal_connect(G_OBJECT(name), "rt-entry-edited", G_CALLBACK(object_name_edited), (gpointer)view);
	GtkWidget	*pos = create_vector3_entry("pos		", view->selected_obj.object->pos, &view->rp->el_prop.pos, element_edited);
	GtkWidget	*rot = create_vector3_entry("rot		", view->selected_obj.object->rot, &view->rp->el_prop.rot, element_edited);

	/* BOUNDING TYPE START  */
	GtkWidget	*bounding_list = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Intersection");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Union");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Substraction");
	gtk_combo_box_set_active(GTK_COMBO_BOX(bounding_list), get_operation_id_from_code(view->selected_obj.object->operation));
	g_signal_connect(bounding_list, "changed", G_CALLBACK(bounding_edited), view);

	/* BOUNDING TYPE END */

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), name);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), pos);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), rot);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), bounding_list);

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), create_scale_entry("Radius	", view->selected_obj.object->radius, &view->rp->el_prop.radius, element_edited));
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), create_scale_entry("Length	", view->selected_obj.object->length, &view->rp->el_prop.length, element_edited));
	create_color_chooser(view, view->selected_obj.object->color);
	gtk_widget_show_all(view->window);
}
