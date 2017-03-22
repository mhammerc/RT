#include "ui.h"

void		init_scene(t_ui *ui)
{
	ui->rp->scene_gtk.ambiant_light = 1.;
	ui->rp->scene_gtk.fov = 45;
	ui->rp->scene_gtk.aa = 0;
	ui->rp->scene_gtk.filter = 0;
}

static void		scene_edited()
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

static void		aa_edited(GtkComboBox *widget, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.aa = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	scene_edited();
}

static void		filters_edited(GtkComboBox *widget, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	ui->rp->scene_gtk.filter = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	scene_edited();
}

static void		ambiant_light_edited(GtkWidget *widget, gdouble value,
					gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->rp->scene_gtk.ambiant_light = value;
	scene_edited();
}

static void		fov_edited(GtkWidget *widget, gdouble value, gpointer data)
{
	t_ui	*ui;

	ui = (t_ui*)data;
	(void)widget;
	ui->rp->scene_gtk.fov = value;
	scene_edited();
}

void			edit_scene_properties(gpointer data)
{
	t_ui		*ui;
	GtkWidget	*aa;
	GtkWidget	*ambiant_light;
	GtkWidget	*fov;

	ui = (t_ui*)data;

	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop),
		gtk_label_new_with_mnemonic("_Scene"));
	ambiant_light = create_scale_entry("Ambiant Light	",
		ui->rp->scene_gtk.ambiant_light, 0, 1);
	g_signal_connect(ambiant_light, "rt-scale-entry-edited",
		G_CALLBACK(ambiant_light_edited), ui);
	fov = create_scale_entry("FOV      	        ",
		ui->rp->scene_gtk.fov, 45, 90);
	g_signal_connect(fov, "rt-scale-entry-edited", G_CALLBACK(fov_edited), ui);

	GtkWidget	*aa_box;
	aa_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget	*aa_title;
	aa_title = gtk_label_new_with_mnemonic("Antialiasing	");
	aa = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "2x2");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "4x4");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(aa), 0, "8x8");
	gtk_combo_box_set_active(GTK_COMBO_BOX(aa), 0);
	g_signal_connect(aa, "changed", G_CALLBACK(aa_edited), ui);
	gtk_widget_set_size_request(aa, 130, 0);
	gtk_container_add(GTK_CONTAINER(aa_box), aa_title);
	gtk_container_add(GTK_CONTAINER(aa_box), aa);

	GtkWidget	*filters_box;
	filters_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget	*filters_title;
	filters_title = gtk_label_new_with_mnemonic("Filters		");
	GtkWidget	*filters;
	filters = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "Black & White");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(filters), 0, "Sepia");
	gtk_combo_box_set_active(GTK_COMBO_BOX(filters), 0);
	g_signal_connect(filters, "changed", G_CALLBACK(filters_edited), ui);
	gtk_widget_set_size_request(filters, 130, 0);

	gtk_container_add(GTK_CONTAINER(filters_box), filters_title);
	gtk_container_add(GTK_CONTAINER(filters_box), filters);

	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), ambiant_light);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), fov);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), aa_box);
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop), filters_box);
}
