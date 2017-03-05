#ifndef RIGHT_PANEL_H
# define RIGHT_PANEL_H

# include "libft.h"
# include "shared.h"


/*
** Constants
*/
typedef struct s_ui				t_ui;

/*
** Maths definitions
*/

typedef struct			s_vector3d
{
	double				x;
	double				y;
	double				z;
}						t_vector3d;

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
}						t_cam_gtk;

typedef struct			s_scene_gtk
{
	GtkWidget			*nb_obj;
	GtkWidget			*nb_spot;
}						t_scene_gtk;

typedef struct			s_element_properties
{
	t_vector3w			pos;
	t_vector3w			lkat;
	GtkWidget			*radius;
	GtkWidget			*length;
}						t_elem_properties;

typedef struct			s_right_panel
{
	GtkWidget			*rp_box;
	GtkWidget			*right_panel;
	GtkWidget			*el_prop_lst;
	GtkWidget			*cam_prop;
	GtkWidget			*scene_prop;
	t_elem_properties	el_prop;
	t_cam_gtk			cam_gtk;
	t_scene_gtk			scene_gtk;
}						t_right_panel;

void		init_scene(t_ui *ui);
void		edit_scene_properties(gpointer data);

void		init_cam(t_ui *ui);
void		edit_cam_properties(gpointer data);

void		edit_element_properties(GtkTreeView *tree_view, GtkTreePath *path,
									GtkTreeViewColumn *column, gpointer data);

#endif
