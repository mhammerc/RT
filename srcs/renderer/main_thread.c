/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <racousin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:29:45 by racousin          #+#    #+#             */
/*   Updated: 2017/04/24 15:46:23 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "renderer.h"
#include "shared.h"

static void		launch_threads(pthread_t *threads,
		t_renderer_thread *threads_data, int i, t_scene *sce)
{
	threads_data[i].sce = monloc(sizeof(t_scene));
	ft_memcpy(threads_data[i].sce, sce, sizeof(t_scene));
	threads_data[i].sce->seed = time(NULL);
	threads_data[i].pixels = sce->pixels;
	threads_data[i].light = sce->light;
	threads_data[i].y_begin = sce->cam.h / CORE_COUNT * i;
	threads_data[i].y_end = sce->cam.h / CORE_COUNT * (i + 1);
	threads_data[i].y_range = threads_data[i].y_end - threads_data[i].y_begin;
	if (pthread_create(&(threads[i]), NULL, thread_compute_image,
				&(threads_data[i])))
	{
		perror("renderer: can not create threads");
		exit(0);
	}
}

static void		finish_rendering(t_scene *sce, t_renderer_thread *threads_data)
{
	int		i;

	light_to_pixel(sce, sce->light, sce->pixels, sce->cam.w * sce->cam.h);
	if (sce->stereo != CAM_LEFT)
	{
		free(sce->light);
		i = 0;
		while (i < CORE_COUNT)
		{
			free(threads_data[i].sce);
			++i;
		}
		free(sce->percent);
		*sce->ui->percent = 1.1;
	}
}

static void		compute_image(t_scene *sce)
{
	int					i;
	pthread_t			threads[CORE_COUNT];
	t_renderer_thread	threads_data[CORE_COUNT];

	i = -1;
	while (++i < CORE_COUNT)
		launch_threads(threads, threads_data, i, sce);
	i = -1;
	while (++i < CORE_COUNT)
		if (pthread_join(threads[i], NULL))
		{
			perror("renderer: can not wait for threads");
			exit(0);
		}
	finish_rendering(sce, threads_data);
}

void			*renderer_compute_image2(void *sce2)
{
	t_scene				*sce;
	t_cam				second_cam;

	sce = (t_scene *)sce2;
	sce->percent = monloc(sizeof(double));
	*sce->percent = 0.;
	*sce->ui->percent = 0.;
	sce->light = (t_vec3*)monloc(sizeof(t_vec3) * sce->cam.w * sce->cam.h);
	if (sce->stereo == CAM_LEFT)
		stereo_camera(sce, &(sce->cam), &second_cam);
	sce->pixels = (int*)monloc(sizeof(int) * sce->cam.w * sce->cam.h
										* (sce->stereo == CAM_LEFT ? 2 : 1));
	compute_image(sce);
	if (sce->stereo == CAM_LEFT)
	{
		stereo_store_first_cam_pixels(sce);
		sce->stereo = CAM_RIGHT;
		sce->cam = second_cam;
		compute_image(sce);
		stereo_join_cam_pixels(sce);
	}
	return (NULL);
}
