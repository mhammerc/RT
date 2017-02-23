#include <gtk/gtk.h>

static void	put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
	int width, height, rowstride, n_channels;
	guchar *pixels, *p;

	n_channels = gdk_pixbuf_get_n_channels (pixbuf);

	g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
	g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
	g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
	g_assert (n_channels == 4);

	width = gdk_pixbuf_get_width (pixbuf);
	height = gdk_pixbuf_get_height (pixbuf);

	g_assert (x >= 0 && x < width);
	g_assert (y >= 0 && y < height);

	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels (pixbuf);

	p = pixels + y * rowstride + x * n_channels;
	p[0] = red;
	p[1] = green;
	p[2] = blue;
	p[3] = alpha;
}

int			main(int argc, char **argv)
{
	GtkBuilder		*builder;
	GtkWidget		*window;
	GtkWidget		*renderer;
	GdkPixbuf		*pixbuf;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "rt_glade.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	gtk_builder_connect_signals(builder, NULL);

	renderer = GTK_WIDGET(gtk_builder_get_object(builder, "img_render"));
	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 1, 8, 250, 250);

	int x;
	int y;
	x = 0;
	while (x < 250)
	{
		y = 0;
		while (y < 250)
		{
			put_pixel(pixbuf, x, y, (guchar)255, (guchar)1, (guchar)1, (guchar)255);
			++y;
		}
		++x;
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(renderer), pixbuf);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();

	return (0);
}


