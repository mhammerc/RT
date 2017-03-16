#include "ui.h"
#include "converter.h"

static void	color_edited(GtkColorButton *button,
		gpointer user_data)
{
	t_ui	*ui;
	GdkRGBA color;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &color);
	ui = (t_ui*)user_data;
	ui->selected_obj.object->color.x = (double)color.red;
	ui->selected_obj.object->color.y = (double)color.green;
	ui->selected_obj.object->color.z = (double)color.blue;
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

void		create_color_chooser(t_ui *ui, t_vec3 color)
{
	GtkWidget	*color_chooser;
	GdkRGBA		gtk_color;

	gtk_color.red = color.x;
	gtk_color.green = color.y;
	gtk_color.blue = color.z;
	gtk_color.alpha = 1;
	gtk_container_add(GTK_CONTAINER(ui->rp->el_prop_lst),
								gtk_label_new_with_mnemonic("_Color Picker"));
	color_chooser = gtk_color_button_new();
	ui->rp->color_chooser = color_chooser;
	g_signal_connect(G_OBJECT(color_chooser), "color-set",
			G_CALLBACK(color_edited), ui);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_chooser), &gtk_color);
	gtk_container_add(GTK_CONTAINER(ui->rp->el_prop_lst), color_chooser);
}
