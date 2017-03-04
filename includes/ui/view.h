#ifndef VIEW_H
# define VIEW_H

# include <gtk/gtk.h>
# include <locale.h>

# include "env.h"

# include "libft.h"
# include "left_panel.h"
# include "right_panel.h"
# include "top_menu.h"
# include "widget.h"

/*
** Interface singleton (just in case, will be removed
*/
t_ui			*get_interface();

/*
** Objects definitions
** See env.h
*/
/*enum e_object_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	EMPTY,
	LIGHT,
	OBJECT_TYPE_COUNT
};
*/

typedef struct			s_object
{
	enum e_object_type	type;
	t_vector3d			pos;
	t_vector3d			lkat;
	double				length;
	double				radius;
	char				name[80];
}						t_object;

typedef struct			s_selected_obj
{
	int					*index;//TODO limit index
	int					depth;
	t_object			*object;
	GtkTreeIter			iter;
}						t_selected_obj;

/*
** Render panel & dependancies
*/

typedef struct			s_display_panel
{
	GtkWidget			*dp_box;
	GtkWidget			*image;
}						t_display_panel;

/*
** t_interface : main structure, holding the entire window and
** everything related.
*/

struct					s_ui
{
	GtkWidget			*window;
	GtkWidget			*main_box;
	GtkWidget			*top_menu;
	GtkWidget			*workspace;

	t_list				*objs;
	t_cam				*cam;
	t_scene				scene;
	t_selected_obj		selected_obj;

	t_left_panel		*lp;
	t_display_panel		*dp;
	t_right_panel		*rp;
};

void					build_interface(GtkApplication *app, gpointer user_data);
void					left_panel(t_ui *ui, t_left_panel *lp);
void					display_panel(t_ui *ui, t_display_panel *dp);
void					right_panel(t_ui *ui, t_right_panel *lp);

/*
** Object and scene manipulation
*/
void					refresh_obj_tree(t_ui *ui);
void					create_sphere();
void					create_plane();
void					create_cone();
void					create_cylinder();
void					create_empty();
void					create_light();

/*
** Homemade widgets
*/
GtkWidget				*create_text_entry(gchar *name, gchar *default_value);
GtkWidget				*create_numeric_entry(char *placeholder, double value, GtkWidget **ref, void *text_edited);
GtkWidget				*create_vector3_entry(gchar *name, t_vector3d value, t_vector3w *ref, void *signal);
GtkWidget				*create_scale_entry(gchar *name, double value, GtkWidget **ref, void *signal);

/*
** Homemade tools that can't live in libft
*/
char					*dtoa(double value);
char					*get_el_type_char(t_object *object);

#endif
