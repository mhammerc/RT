#include <ui.h>

/*
** pixel = pixels + y * rowstride + x * n_channels;
** p[0] = red;
** p[1] = green;
** p[2] = blue;
** p[3] = alpha;
*/
void			ui_print_scene(int *pixels)
{
	t_ui	*ui;
	guchar	*image;

	ui = get_interface();
	image = gdk_pixbuf_get_pixels(ui->dp->pixbuf);
	ft_memcpy(image, pixels, sizeof(int) * RENDER_SIZE_W * RENDER_SIZE_H);
	gtk_image_set_from_pixbuf(GTK_IMAGE(ui->dp->image), ui->dp->pixbuf);
}
