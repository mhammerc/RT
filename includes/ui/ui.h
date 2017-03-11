#ifndef UI_H
# define UI_H

# include <gtk/gtk.h>
# include <locale.h>

// TODO: ui.h isn't supposed to include shared.h
# include "shared.h"

# include "libft.h"
# include "left_panel.h"
# include "right_panel.h"
# include "widget.h"
# include "keys.h"
# include "file_loader.h"
# include "file_saver.h"

# define RENDER_SIZE_W 1280
# define RENDER_SIZE_H 720

/*
** Interface singleton (just in case, will be removed
*/
t_ui			*get_interface();

typedef struct			s_object
{
	enum e_object_type	type;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			color;
	double				length;
	double				radius;
	char				name[80];
	char				operation;
}						t_object;

typedef struct			s_selected_obj
{
	int					*index;//TODO limit index
	int					depth;
	t_object			*object;
	GtkTreeIter			iter;
}						t_selected_obj;

typedef struct			s_ui_cam
{
	t_vec3			pos;
	t_vec3			dir;
}						t_ui_cam;

/*
** Render panel & dependancies
*/
typedef struct			s_display_panel
{
	GtkWidget			*dp_box;
	GtkWidget			*image;
	GdkPixbuf			*pixbuf;
}						t_display_panel;

void					ui_print_scene(int *pixels);

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

	t_left_panel		*lp;
	t_display_panel		*dp;
	t_right_panel		*rp;

	t_menu_file			*file_menu;

	t_list				*objs;
	t_ui_cam			*cam;
	t_scene				scene;
	t_selected_obj		selected_obj;

	int					render_on_change;
	int					lock;
};

void					build_interface(GtkApplication *app, gpointer user_data);
void					left_panel(t_ui *ui, t_left_panel *lp);
void					display_panel(t_ui *ui, t_display_panel *dp);
void					right_panel(t_ui *ui, t_right_panel *lp);

/*
** Object and scene manipulation
*/
void					refresh_obj_tree(t_ui *ui);
void					add_object(t_object object, gboolean render_new);
void					create_sphere();
void					create_plane();
void					create_cone();
void					create_cylinder();
void					create_empty();
void					create_light();

/*
** Homemade tools that can't live in libft
*/
char					*dtoa(double value);
char					*get_el_type_char(t_object *object);

/*
** gtk2cl.c
*/

void					ask_for_new_image(t_ui *ui);

void					load_file(char *filename);
void					hook_up_obj_lst(t_ui *ui, t_env *env);

void					free_obj_tree(t_ui *ui);

#endif
