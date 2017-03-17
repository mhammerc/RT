# include "ui.h"

void			load_file(char *filename)
{
	t_ui			*ui;
	t_env			env;
	GtkDialogFlags	flags;
	GtkWidget		*dialog;

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
		ask_for_new_image(ui);
	}
}

void			hook_up_obj_lst(t_ui *ui, t_env *env)
{
	t_object	cur_obj;

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
