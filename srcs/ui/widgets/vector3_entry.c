#include "view.h"

GtkWidget	*create_vector3_entry(gchar *name, t_vector3d value, t_vector3w *ref, void *signal)
{
	GtkWidget		*box;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(box), gtk_label_new_with_mnemonic(name));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("x", value.x, &(ref->x), signal));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("y", value.y, &(ref->y), signal));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("z", value.z, &(ref->z), signal));
	return (box);
}

GtkWidget	*create_float3_entry(gchar *name, cl_float3 value, t_vector3w *ref, void *signal)
{
	GtkWidget		*box;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(box), gtk_label_new_with_mnemonic(name));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("x", value.x, &(ref->x), signal));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("y", value.y, &(ref->y), signal));
	gtk_container_add(GTK_CONTAINER(box), create_numeric_entry("z", value.z, &(ref->z), signal));
	return (box);
}
