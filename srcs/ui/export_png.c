#include <ui.h>

void 	export_png (void)
{
	GError *error = NULL;
	GdkPixbuf *ref;
	GdkPixbuf *pixbuf;
	t_ui	*ui;

	ui = get_interface();
	gdk_pixbuf_save (ui->dp->pixbuf, "rt_png", "png", &error, NULL);
	g_assert_no_error (error);
}
