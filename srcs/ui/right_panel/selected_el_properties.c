#include "ui.h"
#include "converter.h"
#include "obj_parser.h"
#include <errno.h>

static void		wavefront_file_set(GtkFileChooserButton *widget,
					gpointer user_data)
{
	t_ui		*ui;
	t_object	*object;
	size_t		i;

	ui = (t_ui*)user_data;
	if (ui->rendering)
		return ;
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
	ui->selected_obj.object->filename = gtk_file_chooser_get_filename(
		GTK_FILE_CHOOSER(widget));
	object = parse_wavefront_file(ui->selected_obj.object->filename);
	if (!object)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			"Can not load %s.\nAn error occured.\n%s",
			ui->selected_obj.object->filename, g_strerror(errno));
		g_signal_connect_swapped(dialog, "response", G_CALLBACK(
			gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		ui->selected_obj.object->nb_faces = 0;
		ui->selected_obj.object->faces = 0;
		return ;
	}
	ui->selected_obj.object->nb_faces = object->nb_faces;
	ui->selected_obj.object->faces = object->faces;
}

static void		object_name_edited(GtkWidget *emitter, gchar *new_text,
																gpointer data)
{
	t_object	*obj;
	t_ui		*ui;

	(void)emitter;
	(void)data;
	ui = get_interface();
	obj = ui->selected_obj.object;
	ft_strcpy(obj->name, new_text);
	gtk_tree_store_set(GTK_TREE_STORE(ui->lp->tree.store),
		&ui->selected_obj.iter, 0, obj->name, -1);
}

static void		element_edited()
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
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
	ui->selected_obj.object->operation = get_operation_code_from_id(
		gtk_combo_box_get_active(GTK_COMBO_BOX(widget)));
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

static void		pos_edited(GtkWidget *widget, t_vec3 *pos, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->pos = *pos;
	free(pos);
	element_edited();
}

static void		rot_edited(GtkWidget *widget, t_vec3 *rot, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->rot = *rot;
	free(rot);
	element_edited();
}

static void		radius_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->radius = value;
	element_edited();
}

static void		length_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->length = value;
	element_edited();
}

static void		kdiff_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kdiff = value;
	element_edited();
}

static void		kspec_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->selected_obj.object->kspec = value;
	element_edited();
}

static void		texture_type_edited(GtkComboBox *widget, gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	(void)widget;
	ui->selected_obj.object->have_texture = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	element_edited();
}

static void		texture_file_set(GtkFileChooserButton *widget,
		gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	if (ui->rendering)
		return ;
	free_texture(&ui->selected_obj.object->texture);
	if (ui->selected_obj.object->texture_filename)
		g_free(ui->selected_obj.object->texture_filename);
	ui->selected_obj.object->texture_filename = gtk_file_chooser_get_filename(
													GTK_FILE_CHOOSER(widget));
	ui->selected_obj.object->texture = load_texture(ui->selected_obj.object->texture_filename);
	if (!ui->selected_obj.object->texture.is_valid)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			"Can not load %s.\nIt is not a valid texture.\n%s",
			ui->selected_obj.object->filename, g_strerror(errno));
		g_signal_connect_swapped(dialog, "response", G_CALLBACK(
												gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		return ;
	}
	element_edited();
}


void		 	edit_element_properties(GtkTreeView *tree_view,
					GtkTreePath *path, GtkTreeViewColumn *column, gpointer data)
{
	t_ui				*view;
	t_list				*obj_lst;
	int					*tmp;
	enum e_object_type	type;

	view = (t_ui*)data;
	(void)tree_view;
	(void)column;
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

	GtkWidget	*pos = create_vector3_entry("pos		", view->selected_obj.object->pos);
	GtkWidget	*rot = create_vector3_entry("rot		", view->selected_obj.object->rot);
	g_signal_connect(pos, "rt-vector3-entry-edited", G_CALLBACK(pos_edited), view);
	g_signal_connect(rot, "rt-vector3-entry-edited", G_CALLBACK(rot_edited), view);

	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), name);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), pos);
	gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), rot);

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

	if (type == SPHERE || type == CONE || type == CYLINDER || type == TORUS
			|| type == DISK)
	{
		GtkWidget	*radius = create_scale_entry("Radius	",
			view->selected_obj.object->radius, 0, 1000);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), radius);
		g_signal_connect(radius, "rt-scale-entry-edited",
				G_CALLBACK(radius_edited), view);

	}
	if (type == CONE || type == CYLINDER || type == TORUS || type == POLYGONS)
	{
		GtkWidget	*length = create_scale_entry("Length	",
			view->selected_obj.object->length, 0, 1000);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), length);
		g_signal_connect(length, "rt-scale-entry-edited", G_CALLBACK(length_edited),
			view);
	}

	if (type == SPHERE || type == CYLINDER || type == CONE || type == PLANE
			|| type == TORUS || type == POLYGONS || type == DISK)
	{
		GtkWidget	*kdiff = create_scale_entry("kdiff		",
				view->selected_obj.object->kdiff, 0, 1);
		GtkWidget	*kspec  = create_scale_entry("Kspec	",
				view->selected_obj.object->kspec, 0, 1);
		g_signal_connect(kdiff, "rt-scale-entry-edited", G_CALLBACK(kdiff_edited),
				view);
		g_signal_connect(kspec, "rt-scale-entry-edited", G_CALLBACK(kspec_edited),
				view);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), kdiff);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), kspec);
	}

	if (type != CSG && type != LIGHT)
	{
		create_color_chooser(view, view->selected_obj.object->color);

		GtkWidget	*texture_type_box;
		texture_type_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		GtkWidget	*texture_type_title;
		texture_type_title = gtk_label_new_with_mnemonic("Texture type	");
		GtkWidget	*texture_type = gtk_combo_box_text_new();
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "None");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Spherical");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Sphere damier");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Planar");
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(texture_type), 0, "Planar damier");
		gtk_combo_box_set_active(GTK_COMBO_BOX(texture_type), view->selected_obj.object->have_texture);
		g_signal_connect(texture_type, "changed", G_CALLBACK(texture_type_edited), view);
		gtk_widget_set_size_request(texture_type, 130, 0);
		gtk_container_add(GTK_CONTAINER(texture_type_box), texture_type_title);
		gtk_container_add(GTK_CONTAINER(texture_type_box), texture_type);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), texture_type_box);

		GtkWidget	*texture_box;
		texture_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		GtkWidget	*texture_title;
		texture_title = gtk_label_new_with_mnemonic("Texture		");
		GtkWidget	*texture_chooser;
		texture_chooser = gtk_file_chooser_button_new("Texture images", GTK_FILE_CHOOSER_ACTION_OPEN);
		if (view->selected_obj.object->texture_filename)
			gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(texture_chooser), view->selected_obj.object->texture_filename);
		g_signal_connect(texture_chooser, "file-set", G_CALLBACK(texture_file_set), view);
		gtk_widget_set_size_request(texture_chooser, 130, 0);
		gtk_container_add(GTK_CONTAINER(texture_box), texture_title);
		gtk_container_add(GTK_CONTAINER(texture_box), texture_chooser);
		gtk_container_add(GTK_CONTAINER(view->rp->el_prop_lst), texture_box);
	}

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

void 		refresh_elem_properties(t_ui *ui)
{
	// GList		*children;
	// GList		*iter;
	//
	// children = gtk_container_get_children(GTK_CONTAINER(ui->rp->el_prop));
	// iter = children;
	// while (iter)
	// {
	// 	gtk_widget_destroy(GTK_WIDGET(iter->data));
	// 	iter = g_list_next(iter);
	// }
	// g_list_free(children);
	// gtk_container_add(GTK_CONTAINER(ui->rp->el_prop),
	// 	gtk_label_new_with_mnemonic("_Camera"));
	// ui->rp->pos = create_vector3_entry("pos		", ui->cam->pos);
	// ui->rp->lkat = create_vector3_entry("LookAt	", ui->cam->dir);
	// ui->rp->up = create_vector3_entry("Up           ", ui->cam->up);
	// g_signal_connect(ui->rp->pos, "rt-vector3-entry-edited",
	// 	G_CALLBACK(pos_edited), ui);
	// g_signal_connect(ui->rp->lkat, "rt-vector3-entry-edited",
	// 	G_CALLBACK(dir_edited), ui);
	// g_signal_connect(ui->rp->up, "rt-vector3-entry-edited",
	// 	G_CALLBACK(up_edited), ui);
	// gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->pos);
	// gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->lkat);
	// gtk_container_add(GTK_CONTAINER(ui->rp->cam_prop), ui->rp->up);
	// gtk_widget_show_all(ui->rp->cam_prop);
	(void)ui;
}
