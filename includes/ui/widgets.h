/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:04:43 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 18:17:29 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGETS_H
# define WIDGETS_H

# include <stdlib.h>
# include <gtk/gtk.h>
# include "ui.h"
# include "shared.h"

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
	GtkWidget		*render_on_change;
	GtkWidget		*start_render;
}					t_menu_file;

/*
** Top menu
*/
GtkWidget			*create_top_menu(void);
void				open_dialog_open(void);
void				open_dialog_save(void);
void				open_dialog_export(void);
void				save_scene(char *filename);

/*
** HOMEMADE WIDGETS
*/
GtkWidget			*create_text_entry(gchar *name, gchar *default_value);
GtkWidget			*create_numeric_entry(char *placeholder, gdouble value);
GtkWidget			*create_vector3_entry(gchar *name, t_vec3 value);
GtkWidget			*create_scale_entry(gchar *name, gdouble value,
													gdouble min, gdouble max);

#endif
