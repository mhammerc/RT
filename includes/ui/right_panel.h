/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_panel.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:00:29 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 21:27:37 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIGHT_PANEL_H
# define RIGHT_PANEL_H

/*
** Constants
*/

typedef struct s_ui				t_ui;

/*
** Object properties
*/

typedef struct			s_vector3w
{
	GtkWidget			*x;
	GtkWidget			*y;
	GtkWidget			*z;
}						t_vector3w;

/*
** Right panel & dependancies
*/

typedef struct			s_cam_gtk
{
	t_vector3w			pos;
	t_vector3w			lkat;
	t_vector3w			up;
}						t_cam_gtk;

typedef struct			s_scene_gtk
{
	int					aa;
	double				ambiant_light;
	int					fov;
	enum e_filters		filter;
}						t_scene_gtk;

typedef struct			s_element_properties
{
	t_vector3w			pos;
	t_vector3w			rot;
	GtkWidget			*radius;
	GtkWidget			*length;
	GtkWidget			*kscale;
	GtkWidget			*kspec;
}						t_elem_properties;

typedef struct			s_right_panel
{
	GtkWidget			*rp_box;
	GtkWidget			*right_panel;
	GtkWidget			*el_prop_lst;
	GtkWidget			*cam_prop;
	GtkWidget			*pos;
	GtkWidget			*lkat;
	GtkWidget			*up;
	GtkWidget			*scene_prop;
	GtkWidget			*color_chooser;
	t_elem_properties	el_prop;
	t_cam_gtk			cam_gtk;
	t_scene_gtk			scene_gtk;
}						t_right_panel;

void		init_scene(t_ui *ui);
void		create_ambient_light(t_ui *ui);
void		create_fov_box(t_ui *ui);
void		create_filters_box(t_ui *ui);
void		create_aa_box(t_ui *ui);
void		scene_edited();
void		aa_edited(GtkComboBox *widget, gpointer data);
void		filters_edited(GtkComboBox *widget, gpointer data);
void		ambiant_light_edited(GtkWidget *widget, gdouble value,
																gpointer data);
void		fov_edited(GtkWidget *widget, gdouble value, gpointer data);
void		edit_scene_properties(gpointer data);
void		init_cam(t_ui *ui);
void		edit_cam_properties(gpointer data);
void 		refresh_cam_properties(t_ui *ui);
void		cam_edited();
void		dir_edited(GtkWidget *widget, t_vec3 *dir, gpointer data);
void		up_edited(GtkWidget *widget, t_vec3 *up, gpointer data);
void		clear_properties_list(t_ui *ui);
void		edit_element_properties(GtkTreeView *tree_view, GtkTreePath *path,
									GtkTreeViewColumn *column, gpointer data);
void 		refresh_elem_properties(t_ui *ui);
void		create_color_chooser(t_ui *ui, t_vec3 color);

#endif
