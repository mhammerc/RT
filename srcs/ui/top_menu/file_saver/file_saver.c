# include "ui.h"

void			save_file(char *filename)
{
	t_ui			*ui;
	t_env			env;

	ui = get_interface();
	env.line_count = 0;
	env.entity_lst = NULL;
	env.group_lst = NULL;
	env.group_tmp = NULL;
	ft_init_tabs(&env);
	ft_read_file(filename, &env);
	hook_up_obj_lst(ui, env);
	refresh_obj_tree(ui);
	// g_assert_no_error (error);
}

void			hook_up_obj_scene(t_ui *ui, t_env *env)
{
	t_object	cur_obj;

	env-> = ui->cam.pos;
	env-> = ui->cam.dir;
	while (ui->objs)
	{
		cur_obj = (t_object)(ui->objs->content);
		env-> = cur_obj.type;
		ft_strcpy(env->, cur_obj.name);
		env-> = cur_obj.pos;
		env-> = cur_obj.rot;
		env-> = cur_obj.length;
		env-> = cur_obj.radius;
		env-> = cur_obj.color;
		env-> = env->lst;
		env-> = ui->objs;
		ui->objs = ui->objs->next;
	}
}
