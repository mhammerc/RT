#include "ui.h"

static int		is_numerical(const gchar c)
{
	return ((c >= '0' && c <= '9') || c == '.' || c == '-');
}

static void		text_inserted(GtkEntryBuffer *buffer, guint position,
									gchar *chars, guint n_chars, gpointer data)
{
	t_ui		*ui;
	char		*text;
	size_t		length;

	ui = get_interface();
	if (ui->lock > 0)
	{
		--ui->lock;
		return ;
	}
	ui->lock = 2;

	text = (char*)gtk_entry_buffer_get_text(buffer);
	length = gtk_entry_buffer_get_length(buffer);
	(void)position;
	(void)chars;
	(void)n_chars;
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
	g_signal_emit_by_name((GtkWidget*)data, "rt-numeric-entry-edited",
																atof(new_text));
	free(new_text);
}

static void		text_deleted(GtkEntryBuffer *buffer, guint position,
												guint n_chars, gpointer data)
{
	(void)buffer;
	(void)position;
	(void)n_chars;
	(void)data;
	if (get_interface()->lock > 0)
	{
		--get_interface()->lock;
		return ;
	}
	//get_interface()->lock = 1;
	//g_signal_emit_by_name((GtkWidget*)data, "rt-numeric-entry-edited", atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(data))));
}

GtkWidget		*create_numeric_entry(char *placeholder, gdouble value)
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
	free(value_string);
	gtk_entry_set_max_length(GTK_ENTRY(entry), 5);
	entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
	g_signal_connect_after(entry_buffer, "inserted-text",
											G_CALLBACK(text_inserted), entry);
	g_signal_connect_after(entry_buffer, "deleted-text",
											G_CALLBACK(text_deleted), entry);
	return (entry);
}
