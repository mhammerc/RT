#include "ui.h"
#include "converter.h"
#include "obj_parser.h"
#include <errno.h>

static void		wavefront_file_set(GtkFileChooserButton *widget, gpointer user_data)
{
	t_ui		*ui;
	t_object	*object;
	size_t		i;

	ui = (t_ui*)user_data;
	if (ui->selected_obj.object->filename)
		g_free(ui->selected_obj.object->filename);
	if (ui->selected_obj.object->faces)
	{
		i = 0;
		while (i < ui->selected_obj.object->nb_faces)
		{
			free(ui->selected_obj.object->faces[i].sommets);
			free(ui->selected_obj.object->faces[i].normales);
			free(ui->selected_obj.object->faces[i].textures);
			++i;
		}
		free(ui->selected_obj.object->faces);
	}
	ui->selected_obj.object->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
	object = parse_wavefront_file(ui->selected_obj.object->filename);
	if (!object)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can not load %s.\nAn error occured.\n%s", ui->selected_obj.object->filename, g_strerror(errno));
		g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		return ;
	}
	ui->selected_obj.object->nb_faces = object->nb_faces;
	ui->selected_obj.object->faces = object->faces;
}

static void		object_name_edited(GtkWidget *emitter, gchar *new_text, gpointer data)
{
	t_object			*obj;
	t_ui				*ui;
	GtkTreePath			*path;
	GtkTreeViewColumn	*focus_column;

	ui = get_interface();
	obj = ui->selected_obj.object;
	ft_strcpy(obj->name, new_text);
	gtk_tree_store_set(GTK_TREE_STORE(ui->lp->tree.store), &ui->selected_obj.iter, 0, obj->name, -1);
}

static void		element_edited()
{
	t_object			*obj;
	t_ui				*ui;

	ui = get_interface();
	obj = ui->selected_obj.object;
	obj->pos.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.x)));
	obj->pos.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.y)));
	obj->pos.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.pos.z)));

	obj->rot.x = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.x)));
	obj->rot.y = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.y)));
	obj->rot.z = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.rot.z)));

	if (ui->rp->el_prop.radius)
		obj->radius = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.radius)));
	if (ui->rp->el_prop.length)
		obj->length = atof(gtk_entry_get_text(GTK_ENTRY(ui->rp->el_prop.length)));
	if (ui->render_on_change)
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
	ui->rp->el_prop.length = NULL;
	ui->rp->el_prop.radius = NULL;
}

void		 	edit_element_properties(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer data)
{
	t_ui				*view;
	t_list				*obj_lst;
	int					*tmp;
	enum e_object_type	type;

	view = (t_ui*)data;

	tmp = gtk_tree_path_get_indices_with_depth(path, &(view->selected_obj.depth));
	ft_memcpy(view->selected_obj.index, tmp , 4 * (view->selected_obj.depth));
	obj_lst = ft_lstat_child(view->objs, view->selected_obj.index, view->selected_obj.depth);
	view->selected_obj.object = (t_object*)obj_lst->content;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(view->lp->tree.store), &view->selected_obj.iter, path);

	clear_properties_list(view);

	type = view->selected_obj.object->type;

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), gtk_label_new_with_mnemonic("_Element Properties"));
	GtkWidget	*name = create_text_entry("Name	", view->selected_obj.object->name);
	g_signal_connect(G_OBJECT(name), "rt-entry-edited", G_CALLBACK(object_name_edited), (gpointer)view);
	GtkWidget	*pos = create_vector3_entry("pos		", view->selected_obj.object->pos, &view->rp->el_prop.pos, element_edited);
	GtkWidget	*rot = create_vector3_entry("rot		", view->selected_obj.object->rot, &view->rp->el_prop.rot, element_edited);

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), name);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), pos);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), rot);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), create_scale_entry("Scale	", view->selected_obj.object->radius, &view->rp->el_prop.radius, element_edited));

	if (type == CSG)
	{
		GtkWidget	*bounding_list = gtk_combo_box_text_new();
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "None");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Intersection");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Union");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bounding_list), 0, "Substraction");
		gtk_combo_box_set_active(GTK_COMBO_BOX(bounding_list), get_operation_id_from_code(view->selected_obj.object->operation));
		g_signal_connect(bounding_list, "changed", G_CALLBACK(bounding_edited), view);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), bounding_list);
	}

	if (type == SPHERE || type == CONE || type == CYLINDER)
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), create_scale_entry("Radius	", view->selected_obj.object->radius, &view->rp->el_prop.radius, element_edited));
	if (type == CONE || type == CYLINDER)
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), create_scale_entry("Length	", view->selected_obj.object->length, &view->rp->el_prop.length, element_edited));

	if (type != CSG && type != LIGHT)
		create_color_chooser(view, view->selected_obj.object->color);

	if (type == POLYGONS)
	{
		GtkWidget *file_chooser;
		file_chooser = gtk_file_chooser_button_new(".obj Wavefront model file", GTK_FILE_CHOOSER_ACTION_OPEN);
		if (view->selected_obj.object->filename)
			gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser), view->selected_obj.object->filename);
		g_signal_connect(file_chooser, "file-set", G_CALLBACK(wavefront_file_set), view);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), file_chooser);
	}

	gtk_widget_show_all(view->window);
}
