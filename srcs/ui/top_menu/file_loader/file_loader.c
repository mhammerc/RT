# include "ui.h"

void			load_file(char *filename)
{
	t_ui			*ui;
	t_env			env;
	GtkDialogFlags	flags;
	GtkWidget		*dialog;

	ui = get_interface();
	env.line_count = 0;
	env.entity_lst = NULL;
	env.group_lst = NULL;
	env.group_tmp = NULL;
	ft_bzero(env.error_text, sizeof(char*));
	ft_init_tabs(&env);
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
	ui->cam->dir = env->camera.dir;
	ft_bzero(&cur_obj, sizeof(t_object));
	while (env->entity_lst)
	{
		cur_obj.type = env->entity_lst->entity.type;
		ft_strcpy(cur_obj.name, env->entity_lst->entity.name);
		cur_obj.pos = env->entity_lst->entity.pos;
		cur_obj.rot = env->entity_lst->entity.rot;
		cur_obj.length = env->entity_lst->entity.length;
		cur_obj.radius = env->entity_lst->entity.radius;
		cur_obj.color = env->entity_lst->entity.color;
		cur_obj.kdiff = env->entity_lst->entity.kdiff;
		cur_obj.kspec = env->entity_lst->entity.kspec;
		add_object(cur_obj, FALSE);
		env->entity_lst = env->entity_lst->next;
	}
}
