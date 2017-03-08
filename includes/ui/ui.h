#ifndef UI_H
# define UI_H

# include <gtk/gtk.h>
# include <locale.h>

# include "shared.h"

# include "libft.h"
# include "left_panel.h"
# include "right_panel.h"
# include "widget.h"

# define RENDER_SIZE_W 1366
# define RENDER_SIZE_H 768

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
	t_vec3				pos;
	t_vec3				rot;
	t_vec3				color;
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

struct					s_ui_cam
{
	t_vec3				pos;
	t_vec3				dir;
	/* FLOAT3					up;
	FLOAT3					vx;
	FLOAT3					vy;
	FLOAT3					top_left;
	FLOAT					fov;
	FLOAT					ratio;
	INT						w;
	INT						h;*/
};
typedef struct s_ui_cam		t_ui_cam;

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

	t_list				*objs;
	t_ui_cam			*cam;
	t_scene				scene;
	t_selected_obj		selected_obj;

	t_left_panel		*lp;
	t_display_panel		*dp;
	t_right_panel		*rp;

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

void					open_dialog_save(void);

#endif
