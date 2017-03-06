#include "ui.h"

void		display_panel(t_ui *ui, t_display_panel *dp)
{
	dp->image = gtk_image_new();
	dp->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 1, 8, RENDER_SIZE_W, RENDER_SIZE_H);
	gtk_widget_set_size_request(dp->image, RENDER_SIZE_W, RENDER_SIZE_H);
	gtk_container_add(GTK_CONTAINER(ui->workspace), dp->image);
}
