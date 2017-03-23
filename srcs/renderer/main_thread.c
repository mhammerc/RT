#include "ui.h"
#include "renderer.h"
#include "shared.h"

static void		launch_threads(pthread_t *threads,
		t_renderer_thread *threads_data, int i, t_scene *sce)
{
	threads_data[i].sce = malloc(sizeof(t_scene));
	ft_memcpy(threads_data[i].sce, sce, sizeof(t_scene));
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

	light_apply_filters(sce, sce->light, sce->cam.w, sce->cam.h);
	light_to_pixel(sce->light, sce->pixels, sce->cam.w, sce->cam.h);
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

void			*renderer_compute_image2(void *sce2)
{
	pthread_t			threads[CORE_COUNT];
	t_renderer_thread	threads_data[CORE_COUNT];
	int					i;
	t_vec3				*light;
	t_scene				*sce;

	sce = (t_scene *)sce2;
	sce->percent = malloc(sizeof(double));
	*sce->percent = 0.;
	*sce->ui->percent = 0.;
	sce->pixels = (int*)malloc(sizeof(int) * sce->cam.w * sce->cam.h);
	light = (t_vec3*)malloc(sizeof(t_vec3) * sce->cam.w * sce->cam.h);
	sce->light = light;
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
	return (NULL);
}
