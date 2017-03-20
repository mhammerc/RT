# include "ui.h"
# include "obj_parser.h"

void			load_file(char *filename)
{
	t_ui			*ui;
	t_env			env;

	ui = get_interface();
	ft_bzero(&env, sizeof(t_env));
	ft_read_file(filename, &env);
	if (env.error_text[0] != '\0')
		return ;
	else
	{
		free_obj_tree(ui);
		hook_up_obj_lst(ui, &env);
		refresh_obj_tree(ui);
		refresh_cam_properties(ui);
		ask_for_new_image(ui);
	}
}

static void		load_polygons(t_list *objects)
{
	t_object	*object;
	t_object	*new;

	if (!objects)
		return ;
	object = (t_object*)objects->content;
	if (object->type == POLYGONS && *object->filename != 0)
	{
		new = parse_wavefront_file(object->filename);
		if (new)
		{
			object->faces = new->faces;
			object->nb_faces = new->nb_faces;
		}
	}
	if (objects->children)
		load_polygons(objects->children);
	if (objects->next)
		load_polygons(objects->next);
}

void			hook_up_obj_lst(t_ui *ui, t_env *env)
{
	load_polygons(env->objects);
	ui->cam->pos = env->camera.pos;
	ui->cam->dir = env->camera.look_at;
	//todo update camera in interface
	ui->objs = env->objects;
/*	ft_bzero(&cur_obj, sizeof(t_object));
	while (env->objects)
	{
		add_object(env->objects, FALSE);
		env->objects =
	}
	*/
}
