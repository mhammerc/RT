/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:47:56 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 14:23:13 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void		inserted_text(GtkEntryBuffer *buffer, guint position,
								gchar *chars, guint n_chars, gpointer widget)
{
	(void)position;
	(void)chars;
	(void)n_chars;
	g_signal_emit_by_name((GtkWidget*)(widget), "rt-entry-edited",
											gtk_entry_buffer_get_text(buffer));
}

static void		deleted_text(GtkEntryBuffer *buffer, guint position,
					guint n_chars, gpointer widget)
{
	(void)position;
	(void)n_chars;
	g_signal_emit_by_name((GtkWidget*)(widget), "rt-entry-edited",
											gtk_entry_buffer_get_text(buffer));
}

GtkWidget		*create_text_entry(gchar *name, gchar *default_value)
{
	GtkWidget		*hbox;
	GtkWidget		*label;
	GtkWidget		*text_entry;
	GtkEntryBuffer	*text_buffer;

	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	label = gtk_label_new_with_mnemonic(name);
	text_entry = gtk_entry_new();
	text_buffer = gtk_entry_get_buffer(GTK_ENTRY(text_entry));
	if (default_value)
		gtk_entry_buffer_set_text(text_buffer, default_value, -1);
	gtk_container_add(GTK_CONTAINER(hbox), label);
	gtk_container_add(GTK_CONTAINER(hbox), text_entry);
	gtk_entry_set_max_length(GTK_ENTRY(text_entry), 15);
	g_signal_connect(GTK_ENTRY_BUFFER(text_buffer), "inserted-text",
		G_CALLBACK(inserted_text), (gpointer)hbox);
	g_signal_connect(GTK_ENTRY_BUFFER(text_buffer), "deleted-text",
		G_CALLBACK(deleted_text), (gpointer)hbox);
	return (hbox);
}
