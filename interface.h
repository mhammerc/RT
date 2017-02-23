#ifndef INTERFACE_H
# define INTERFACE_H

# include <gtk/gtk.h>

typedef struct			s_interface
{
	GtkBuilder			*builder;
	GtkWidget			*window;
	GtkWidget			*image;
	GdkPixbuf			*pixbuf;
}						t_interface;

void			interface_print_scene(int *pixels);

void			interface_init(int argc, char **argv);
t_interface		*interface_get();

#endif
