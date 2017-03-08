/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfour <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:30:04 by vfour             #+#    #+#             */
/*   Updated: 2017/02/06 18:51:40 by vfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "rtv1.h"

void		usage(void)
{
	ft_putendl("usage: ./rtv1 [options] scene_file");
	ft_putendl("options:");
	ft_putendl("\t-w=window_width\n\t-h=window_height");
}

int			main(int argc, char **argv)
{
	t_env	*e;

	if (argc < 2)
	{
		usage();
		return (EXIT_SUCCESS);
	}
	if (NULL == (e = new_env(argc, argv)))
		ft_exit("Malloc error", EXIT_FAILURE);
	if (NULL == (e->sce = parse_scene(e->scene_file, e->w, e->h)))
		ft_exit("Scene parser error", EXIT_FAILURE);
	init_mlx(e);
	draw(e);
	mlx_loop(e->mlx_ptr);
	return (EXIT_SUCCESS);
}
