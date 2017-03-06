#include "ui.h"

static int		is_numerical(const gchar c)
{
	return ((c >= '0' && c <= '9') || c == '.' || c == '-');
}

static void		numeric_entry_text_inserted(GtkEntryBuffer *buffer, guint position, gchar *chars, guint n_chars, gpointer text_edited_function)
{
	if (get_interface()->lock)
		return ;
	get_interface()->lock = 1;

	void(*f)();
	const gchar	*text = gtk_entry_buffer_get_text(buffer);
	const gint	length = gtk_entry_buffer_get_length(buffer);
	gchar		*new_text;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	new_text = malloc(sizeof(gchar) * (length + 1));
	while (i < length)
	{
		if (is_numerical(text[i]))
			new_text[j++] = text[i];
		++i;
	}
	new_text[j] = 0;
	gtk_entry_buffer_set_text(buffer, new_text, -1);
	f = text_edited_function;
	f();
}

static void		numeric_entry_text_deleted(GtkEntryBuffer *buffer, guint position, guint n_chars, gpointer user_data)
{
	void(*f)();

	if (get_interface()->lock)
		return ;
	get_interface()->lock = 1;
	f = user_data;
	f();
}

GtkWidget		*create_numeric_entry(char *placeholder, double value, GtkWidget  **ref, void *text_edited)
{
	GtkWidget		*entry;
	GtkEntryBuffer	*entry_buffer;
	char			*value_string;

	entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(entry), 5);
	if (placeholder)
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
	value_string = dtoa(value);
	gtk_entry_set_text(GTK_ENTRY(entry), value_string);
	gtk_entry_set_max_length(GTK_ENTRY(entry), 6);
	free(value_string);
	entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
	g_signal_connect(entry_buffer, "inserted-text", G_CALLBACK(numeric_entry_text_inserted), text_edited);
	g_signal_connect(entry_buffer, "deleted-text", G_CALLBACK(numeric_entry_text_deleted), text_edited);
	if (ref)
		*ref = entry;
	return (entry);
}
