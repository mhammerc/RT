#include "view.h"

static gboolean		scale_entry_scale_edited(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer data)
{
	GtkEntryBuffer	*buffer;
	static int		lock = 0;

	if (lock)
	{
		lock = 0;
		return (0);
	}
	lock = 1;
	(void)range;
	(void)scroll;
	buffer = (GtkEntryBuffer*)data;
	gtk_entry_buffer_set_text(buffer, ft_itoa(value), -1);
	return (0);
}

static void			scale_entry_number_edited(GtkEntryBuffer *buffer, guint position, gchar *chars, guint n_chars, gpointer data)
{
	static int	lock = 0;
	GtkWidget	*scale;
	gchar		*content;
	double		value;

	if (lock)
	{
		lock = 0;
		return ;
	}
	lock = 1;
	scale = (GtkWidget*)data;
	content = (gchar*)gtk_entry_buffer_get_text(buffer);
	value = strtod(content, NULL);
	gtk_range_set_value(GTK_RANGE(scale), value);
}

GtkWidget			*create_scale_entry(gchar *name, double value, GtkWidget **ref, void* signal)
{
	GtkWidget		*box;
	GtkWidget		*label;
	GtkWidget		*scale;
	GtkWidget		*entry;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	label = gtk_label_new_with_mnemonic(name);
	scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 1000, 1);
	gtk_range_set_value(GTK_RANGE(scale), value);
	entry = create_numeric_entry("0", value, ref, signal);
	gtk_widget_set_size_request(scale, 100, 0);
	gtk_container_add(GTK_CONTAINER(box), label);
	gtk_container_add(GTK_CONTAINER(box), scale);
	gtk_container_add(GTK_CONTAINER(box), entry);
	g_signal_connect(scale, "change-value", G_CALLBACK(scale_entry_scale_edited), gtk_entry_get_buffer(GTK_ENTRY(entry)));
	g_signal_connect(gtk_entry_get_buffer(GTK_ENTRY(entry)), "inserted-text", G_CALLBACK(scale_entry_number_edited), scale);
	return (box);
}
