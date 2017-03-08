/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:17:00 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 19:55:40 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include <limits.h>
#include "rtv1.h"

/*
** Parse integer argument given in command line arg
** @return parsed int or default value
*/

static int		get_intarg(char **argv,
		char *arg,
		char *default_value,
		int (*f)(const char*))
{
	int		i;
	int		ret;

	i = 1;
	ret = -1;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], arg, ft_strlen(arg)) == 0)
		{
			ret = (*f)(argv[i] + ft_strlen(arg));
			break ;
		}
		++i;
	}
	if (ret < 0)
		return ((*f)(default_value));
	return (ret);
}

/*
** cc
*/

static char		*get_scene_file(int argc, char **argv)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (ft_strdup(argv[i]));
		++i;
	}
	return (NULL);
}

/*
** Create a new empty universe according to main args
** @return a new env or null
*/

t_env			*new_env(int argc, char **argv)
{
	t_env		*e;

	(void)argc;
	if ((e = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	e->h = get_intarg(argv, "-h=", DEFAULT_HEIGHT, &ft_atoi);
	e->w = get_intarg(argv, "-w=", DEFAULT_WIDTH, &ft_atoi);
	e->h = e->h > MIN_HEIGHT ? e->h : MIN_HEIGHT;
	e->w = e->w > MIN_WIDTH ? e->w : MIN_WIDTH;
	e->h = e->h < MAX_HEIGHT ? e->h : MAX_HEIGHT;
	e->w = e->w < MAX_WIDTH ? e->w : MAX_WIDTH;
	e->scene_file = get_scene_file(argc, argv);
	e->mouse_x = INT_MIN;
	e->mouse_y = INT_MIN;
	return (e);
}

/*
** Initialize mlx (once scene is parsed and valid)
** @return nothing but exits if initialization fails
*/

void			init_mlx(t_env *e)
{
	if (!(e->mlx_ptr = mlx_init())
		|| !(e->win_ptr = mlx_new_window(e->mlx_ptr, e->w, e->h, "RTv1"))
		|| !(e->img_ptr = mlx_new_image(e->mlx_ptr, e->w, e->h))
		|| !(e->img = (int*)mlx_get_data_addr(e->img_ptr, &(e->bpp),
					&(e->size_line), &(e->endian))))
		ft_exit("mlx initialization failed", EXIT_FAILURE);
	e->color = color_tab_new(e->w, e->h, e->img);
	init_hooks(e);
}
