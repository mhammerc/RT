/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:33:28 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 11:18:42 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void			init_scene(t_ui *ui)
{
	ui->rp->scene_gtk.ambiant_light = 1.;
	ui->rp->scene_gtk.fov = 45;
	ui->rp->scene_gtk.aa = 0;
	ui->rp->scene_gtk.filter = 0;
}


void		scene_edited(void)
{
	t_ui	*ui;

	ui = get_interface();
	if (ui->render_on_change)
		ask_for_new_image(ui);
}

void			edit_scene_properties(gpointer data)
{
	t_ui		*ui;

	ui = (t_ui*)data;
	gtk_container_add(GTK_CONTAINER(ui->rp->scene_prop),
		gtk_label_new_with_mnemonic("_Scene"));
	create_ambient_light(ui);
	create_fov_box(ui);
	create_filters_box(ui);
	create_aa_box(ui);
}