#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "ui.h"
#include "renderer.h"
#include "shared.h"
#include "texture_loader.h"

void			update_progress_bar(t_scene *scene, double percent_per_line)
{
	static double	last_percent = 0.;

	*scene->percent += percent_per_line;
	if (*scene->percent > 0.99)
	{
		last_percent = 0.;
	}
	else if (*scene->percent - last_percent > 0.0001)
	{
		last_percent = *scene->percent;
		*scene->ui->percent = last_percent;
	}
}

int				check_renderer(void *data)
{
	t_scene	*scene;

	scene = (t_scene*)data;
	pthread_mutex_lock(&scene->ui->mutex_stock);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(scene->ui->progress_bar),
			*scene->ui->percent);
	if (*scene->ui->percent == 1.1)
	{
		ui_print_scene(scene->pixels);
		free(scene->pixels);
		pthread_mutex_unlock(&scene->ui->mutex_stock);
		scene->ui->rendering = 0;
		return (FALSE);
	}
	pthread_mutex_unlock(&scene->ui->mutex_stock);
	return (TRUE);
}

void			renderer_compute_image(t_scene *sce)
{
	pthread_t thread;

	sce->ui->rendering = 1;
	pthread_create(&thread, NULL, renderer_compute_image2, sce);
	pthread_detach(thread);
	gdk_threads_add_timeout(100, check_renderer, sce);
}
