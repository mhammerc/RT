/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_csg_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:34:09 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/23 02:00:12 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static char	get_operation_code_from_id(int id)
{
	if (id == 1)
		return ('I');
	if (id == 2)
		return ('U');
	if (id == 3)
		return ('-');
	return ('0');
}

static int	get_operation_id_from_code(char code)
{
	if (code == 'I')
		return (1);
	if (code == 'U')
		return (2);
	if (code == '-')
		return (3);
	return (0);
}

static void	bounding_upd(GtkComboBox *widget, gpointer user_data)
{
	t_ui	*ui;

	ui = (t_ui*)user_data;
	ui->selected_obj.object->operation = get_operation_code_from_id(
		gtk_combo_box_get_active(GTK_COMBO_BOX(widget)));
	ask_for_new_image(ui);
}

void		add_csg_widgets(t_ui *ui, t_object *focused_obj, GtkWidget *props)
{
	GtkWidget	*bound_box;
	GtkWidget	*bound_title;
	GtkWidget	*bound;

	bound_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	bound_title = gtk_label_new_with_mnemonic("Operation	");
	bound = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bound), 0, "None");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bound), 0, "Intersection");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bound), 0, "Union");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(bound), 0, "Substraction");
	gtk_combo_box_set_active(GTK_COMBO_BOX(bound),
							get_operation_id_from_code(focused_obj->operation));
	g_signal_connect(bound, "changed", G_CALLBACK(bounding_upd), ui);
	gtk_widget_set_size_request(bound, 130, 0);
	gtk_container_add(GTK_CONTAINER(bound_box), bound_title);
	gtk_container_add(GTK_CONTAINER(bound_box), bound);
	gtk_container_add(GTK_CONTAINER(props), bound_box);
}
