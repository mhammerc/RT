#include "ui.h"

static gboolean		scale_edited(GtkRange *range, GtkScrollType scroll,
		gdouble value, gpointer data)
{
	GtkEntryBuffer	*buffer;
	GtkWidget		*box;

	(void)range;
	(void)scroll;
	box = (GtkWidget*)data;
	GList	*childs;
	childs = gtk_container_get_children(GTK_CONTAINER(box));
	childs = childs->next;
	childs = childs->next;
	buffer = gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)childs->data));
	gtk_entry_buffer_set_text(buffer, ft_itoa(value), -1);
	g_signal_emit_by_name(box, "rt-scale-entry-edited", value);
	return (0);
}

static void			entry_edited(GtkWidget *entry, gpointer data)
{
	GtkWidget		*box;
	GtkEntryBuffer	*buffer;
	GtkWidget		*scale;
	gchar			*content;
	double			value;

	(void)entry;
	box = (GtkWidget*)data;
	GList	*childs;
	childs = gtk_container_get_children(GTK_CONTAINER(box));
	childs = childs->next;
	scale = (GtkWidget*)childs->data;

	childs = childs->next;
	buffer = gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)childs->data));

	content = (gchar*)gtk_entry_buffer_get_text(buffer);
	value = atof(content);
	gtk_range_set_value(GTK_RANGE(scale), value);
	g_signal_emit_by_name(box, "rt-scale-entry-edited", value);
}

GtkWidget			*create_scale_entry(gchar *name, gdouble value, gdouble min,
																	gdouble max)
{
	GtkWidget		*box;
	GtkWidget		*label;
	GtkWidget		*scale;
	GtkWidget		*entry;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	label = gtk_label_new_with_mnemonic(name);
	scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min, max, 1);
	gtk_range_set_value(GTK_RANGE(scale), value);
	entry = create_numeric_entry(name, value);
	gtk_widget_set_size_request(scale, 100, 0);
	gtk_container_add(GTK_CONTAINER(box), label);
	gtk_container_add(GTK_CONTAINER(box), scale);
	gtk_container_add(GTK_CONTAINER(box), entry);
	g_signal_connect(scale, "change-value", G_CALLBACK(scale_edited), box);
	g_signal_connect(entry, "rt-numeric-entry-edited", G_CALLBACK(entry_edited),
																		box);
	return (box);
}
