#include "rt.h"
#include <string.h>

t_interface		*interface_get()
{
	static t_interface	interface = {};

	return (&interface);
}

/*
** pixel = pixels + y * rowstride + x * n_channels;
** p[0] = red;
** p[1] = green;
** p[2] = blue;
** p[3] = alpha;
*/
void			interface_print_scene(int *pixels)
{
	t_interface	*interface;
	guchar *image;

	interface = interface_get();
	image = gdk_pixbuf_get_pixels (interface->pixbuf);
	ft_memcpy(image, pixels, sizeof(int) * 800 * 600);
	gtk_image_set_from_pixbuf(GTK_IMAGE(interface->image), interface->pixbuf);
}

void			interface_init(int argc, char **argv)
{
	t_interface		*interface;

	interface = interface_get();
	gtk_init(&argc, &argv);
	interface->builder = gtk_builder_new();
	gtk_builder_add_from_file(interface->builder, "resources/rt_glade.glade",
			NULL);
	interface->window = GTK_WIDGET(gtk_builder_get_object(interface->builder,
				"main_window"));
	gtk_builder_connect_signals(interface->builder, NULL);
	interface->image = GTK_WIDGET(gtk_builder_get_object(interface->builder,
				"img_render"));
	interface->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 1, 8, 800, 600);
	opencl_compute_image();
	gtk_widget_show(interface->window);
	gtk_main();
}
