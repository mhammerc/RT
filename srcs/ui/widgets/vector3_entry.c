#include "ui.h"

GtkWidget	*create_vector3_entry(gchar *name, t_vector3d value, t_vector3w *ref, void *signal)
{
	GtkWidget		*box;
	GtkWidget		*entry_x;
	GtkWidget		*entry_y;
	GtkWidget		*entry_z;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(box), gtk_label_new_with_mnemonic(name));

	entry_x = create_numeric_entry("x", value.x, &(ref->x), signal);
	entry_y = create_numeric_entry("y", value.y, &(ref->y), signal);
	entry_z = create_numeric_entry("z", value.z, &(ref->z), signal);
	return (box);
}
