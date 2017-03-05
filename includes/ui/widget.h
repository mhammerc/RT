/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:09:47 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/03 16:08:22 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_H
# define WIDGET_H

# include <stdlib.h>
# include <gtk/gtk.h>

# include "ui.h"

/*
** top menu (file, open, save, ..)
*/
typedef struct		s_menu_file
{
	GtkWidget		*menu;
	GtkWidget		*file;
	GtkWidget		*open;
	GtkWidget		*save;
	GtkWidget		*export;
	GtkWidget		*quit;
}					t_menu_file;

GtkWidget				*create_top_menu(void);

/*
** HOMEMADE WIDGETS
*/
GtkWidget				*create_text_entry(gchar *name, gchar *default_value);
GtkWidget				*create_numeric_entry(char *placeholder, double value,
		GtkWidget **ref, void *text_edited);
GtkWidget				*create_vector3_entry(gchar *name, t_vector3d value,
		t_vector3w *ref, void *signal);
GtkWidget				*create_scale_entry(gchar *name, double value,
		GtkWidget **ref, void *signal);

#endif
