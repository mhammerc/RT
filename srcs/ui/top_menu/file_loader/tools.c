#include "ui.h"

void		ft_free_split(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
	{
		free(tab[count]);
		count++;
	}
	free(tab);
}

void 		ft_puterr(int err, t_env *env)
{
	t_ui			*ui;
	int				check_first_err;
	GtkDialogFlags	flags;
	GtkWidget		*dialog;

	ui = get_interface();
	check_first_err = 0;
	if (env->error_text[0] != '\0')
		check_first_err = 1;
	if (check_first_err != 0)
		return ;
	if (err == ERR_FILE_OPEN)
		ft_strcpy(env->error_text, "Error : could not open this file");
	else if (err == ERR_FILE_SYNTAX)
		ft_strcpy(env->error_text, "Error : syntax error");
	else if (err == ERR_WRONG_ARGS)
		ft_strcpy(env->error_text, "Error : the program only takes one argument");
	else if (err == ERR_NO_ENTITY)
		ft_strcpy(env->error_text, "Error : no object or light found, it's either incomplete or empty");
	else if (err == ERR_UNKNOWN_OBJ)
		ft_strcpy(env->error_text, "Error : this type of object does not exist");
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window), flags, GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE, "%s\n", env->error_text);
	 gtk_dialog_run(GTK_DIALOG(dialog));
	 gtk_widget_destroy(dialog);
}

void		ft_free_list(t_entity_lst **entity_lst)
{
	t_entity_lst	*tmp;
	t_entity_lst	*tmp2;

	tmp = *entity_lst;
	if (!*entity_lst)
		return ;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	*entity_lst = NULL;
}

t_entity_lst	*ft_cpy_lst(t_entity_lst *entity_lst)
{
	t_entity_lst	*tmp;
	t_entity_lst	*tmp2;
	t_entity_lst	*new;

	tmp = entity_lst;
	tmp2 = NULL;
	new = NULL;
	while (tmp)
	{
		tmp2 = ft_new_entity(tmp->entity);
		ft_push_entity(&new, tmp2);
		tmp = tmp->next;
	}
	return (new);
}
