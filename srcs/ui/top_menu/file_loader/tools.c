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

void		ft_puterr(int err, t_env *env)
{
	if (err == ERR_FILE_OPEN)
		ft_putendl("Error : could not open this file");
	else if (err == ERR_FILE_SYNTAX)
	{
		ft_putstr("Error : syntax error line : ");
		ft_putnbr(env->line_count);
		ft_putchar('\n');
	}
	else if (err == ERR_WRONG_ARGS)
		ft_putendl("Error : the program only takes one argument");
	else if (err == ERR_NO_ENTITY)
		ft_putendl(
	"Error : no object or light found, it's either incomplete or empty");
	else if (err == ERR_UNKNOWN_OBJ)
		ft_putendl("Error : this type of object does not exist");
	exit(1);
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
