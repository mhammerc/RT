/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:05:41 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 18:19:21 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(int argc, char **argv)
{
	static GtkApplication	*app;
	int						status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(init_interface), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return (status);
}
