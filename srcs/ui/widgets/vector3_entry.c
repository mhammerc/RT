#include "ui.h"

static void	vector3_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	GtkWidget	*box;
	t_vector3w	group;
	t_vec3		*values;
	GList		*childs;

	(void)widget;
	(void)value;
	box = (GtkWidget*)data;
	childs = gtk_container_get_children(GTK_CONTAINER(box));
	childs = childs->next;
	group.x = (GtkWidget*)childs->data;
	childs = childs->next;
	group.y = (GtkWidget*)childs->data;
	childs = childs->next;
	group.z = (GtkWidget*)childs->data;
	//FIXME bien utiliser les listes

	values = malloc(sizeof(t_vec3));
	values->x = atof(gtk_entry_buffer_get_text(
		gtk_entry_get_buffer(GTK_ENTRY(group.x))));
	values->y = atof(gtk_entry_buffer_get_text(
		gtk_entry_get_buffer(GTK_ENTRY(group.y))));
	values->z = atof(gtk_entry_buffer_get_text(
		gtk_entry_get_buffer(GTK_ENTRY(group.z))));
	g_signal_emit_by_name(box, "rt-vector3-entry-edited", values);
}

GtkWidget	*create_vector3_entry(gchar *name, t_vec3 value)
{
	GtkWidget		*box;
	GtkWidget		*label;
	t_vector3w		group;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	label = gtk_label_new_with_mnemonic(name);
	group.x = create_numeric_entry("x", value.x);
	group.y = create_numeric_entry("y", value.y);
	group.z = create_numeric_entry("s", value.z);
	gtk_container_add(GTK_CONTAINER(box), label);
	gtk_container_add(GTK_CONTAINER(box), group.x);
	gtk_container_add(GTK_CONTAINER(box), group.y);
	gtk_container_add(GTK_CONTAINER(box), group.z);
	g_signal_connect(group.x, "rt-numeric-entry-edited",
		G_CALLBACK(vector3_edited), box);
	g_signal_connect(group.y, "rt-numeric-entry-edited",
		G_CALLBACK(vector3_edited), box);
	g_signal_connect(group.z, "rt-numeric-entry-edited",
		G_CALLBACK(vector3_edited), box);
	return (box);
}
