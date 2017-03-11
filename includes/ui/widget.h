#ifndef WIDGET_H
# define WIDGET_H

# include <stdlib.h>
# include <gtk/gtk.h>

# include "ui.h"
# include "shared.h"

/*
** top menu (file, open, save, ..)
*/
typedef struct		s_menu_file
{
	GtkWidget		*menu;
	GtkWidget		*file;
	GtkWidget		*open;
	GtkWidget		*save;
	GtkWidget		*export;
	GtkWidget		*quit;
	GtkWidget		*render_on_change;
	GtkWidget		*start_render;
}					t_menu_file;

/*
** Top menu
*/
GtkWidget				*create_top_menu(void);
void					open_dialog_open(void);
void					open_dialog_save(void);
void					open_dialog_export(void);

/*
** HOMEMADE WIDGETS
*/
GtkWidget				*create_text_entry(gchar *name, gchar *default_value);
GtkWidget				*create_numeric_entry(char *placeholder, double value,
		GtkWidget **ref, void *text_edited);
GtkWidget				*create_vector3_entry(gchar *name, t_vec3 value,
		t_vector3w *ref, void *signal);
GtkWidget				*create_scale_entry(gchar *name, double value,
		GtkWidget **ref, void *signal);

#endif
