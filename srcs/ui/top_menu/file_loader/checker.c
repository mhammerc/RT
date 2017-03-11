#include "ui.h"

void	ft_init_tabs(t_env *env)
{
	int	count;

	count = -1;
	env->entity_type = UNDEFINED;
	env->group_entity_type = UNDEFINED;
	while (++count < MAX_INDEX_SCENE)
		env->scene_filled[count] = 0;
	count = -1;
	while (++count < MAX_INDEX_CAMERA)
		env->camera_filled[count] = 0;
	count = -1;
	while (++count < MAX_INDEX_OBJECT)
		env->object_filled[count] = 0;
	count = -1;
}

int		ft_check_all(t_env *env)
{
	int	count;

	count = -1;
	while (++count < MAX_INDEX_SCENE)
	{
		if (env->scene_filled[count] == 0)
			return (0);
	}
	count = -1;
	while (++count < MAX_INDEX_CAMERA)
	{
		if (env->camera_filled[count] == 0)
			return (0);
	}
	return (1);
}

int		ft_check_entity(t_env *env, int entity_type)
{
	int	count;

	count = -1;
	if (entity_type == OBJECT)
	{
		while (++count < MAX_INDEX_OBJECT)
		{
			if (env->object_filled[count] == 0)
				return (0);
		}
	}
	return (1);
}

void	ft_reset(t_env *env, int entity_type)
{
	int	count;

	count = -1;
	if (entity_type == OBJECT)
	{
		while (++count < MAX_INDEX_OBJECT)
			env->object_filled[count] = 0;
	}
}
