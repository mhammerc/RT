/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_menu_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:03:32 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 16:36:39 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

int		on_key_press_window(GtkWidget *widget, GdkEventKey *event,
															gpointer user_data)
{
	t_ui		*ui;

	ui = get_interface();
	(void)widget;
	(void)user_data;
	if (event->keyval == GDK_KEY_Escape)
		ft_exit_fd("Closing RT.", 1);
	else if (event->keyval == GDK_KEY_F1)
		open_dialog_open();
	else if (event->keyval == GDK_KEY_F2)
		open_dialog_save();
	else if (event->keyval == GDK_KEY_F3)
		open_dialog_export();
	else if (event->keyval == GDK_KEY_F4)
		printf("F4 key pressed\n");
	else if (event->keyval == GDK_KEY_F5)
		printf("F5 key pressed\n");
	return (FALSE);
}

void	event_handler_window(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->window), "key_press_event",
										G_CALLBACK(on_key_press_window), NULL);
}

void	event_handler_display(t_ui *ui)
{
	g_signal_connect(G_OBJECT(ui->lp->tree.tree), "key_press_event",
										G_CALLBACK(on_key_press_display), NULL);
}
