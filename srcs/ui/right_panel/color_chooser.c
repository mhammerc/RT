#include "ui.h"

void		edit_color(gpointer data)
{
	t_ui		*view;
	GtkWidget	*color_chooser;
//	t_scene		*scene;

	view = (t_ui*)data;
	gtk_container_add(GTK_CONTAINER(view->rp->color_chooser), gtk_label_new_with_mnemonic("_Color Picker"));
	color_chooser = gtk_color_chooser_widget_new();
	//GTK_COLOR_CHOOSER_WIDGET(color_chooser)->show_editor = TRUE;
	GValue value;
	ft_bzero(&value, sizeof(GValue));
	g_value_init(&value, G_TYPE_BOOLEAN);
	g_value_set_boolean(&value, TRUE);
	g_object_set_property(G_OBJECT(color_chooser), "show-editor", &value);
	gtk_container_add(GTK_CONTAINER(view->rp->color_chooser), color_chooser);

	gtk_widget_show_all(view->window);
}
