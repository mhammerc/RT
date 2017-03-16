#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "ui.h"
#include "renderer.h"
#include "shared.h"


static void		update_progress_bar(t_scene *scene, double percent_per_line)
{
	static double	last_percent = 0.;

	*scene->percent += percent_per_line;
	if (*scene->percent > 0.95)
	{
		last_percent = 0.;
	}
	else if (*scene->percent - last_percent > 0.0001)
	{
		last_percent = *scene->percent;
		*scene->ui->percent = last_percent;
	}
}

t_list			*ft_lstdup(t_list	*original_begin)
{
	t_list	*original;
	t_list	*original_cpy;
	t_list	*n;
	t_obj	*obj;

	n = NULL;
	original = original_begin;
	while (original)
	{
		original_cpy = ft_lstnew(original->content, original->content_size);
		//original_cpy = malloc(sizeof(t_list));
		//original_cpy->content = malloc(sizeof(t_obj));
		//memcpy(original_cpy->content, original->content, sizeof(t_obj));
		obj = (t_obj*)original_cpy->content;
		if (obj->type == POLYGONS)
		{
			t_face	*faces = malloc(sizeof(t_face) * obj->nb_faces);
			memcpy(faces, obj->faces, sizeof(t_face) * obj->nb_faces);
			obj->faces = faces;
		}
		ft_lstadd(&n, original_cpy);
		original = original->next;
	}
	return (n);
}

static void		*thread_compute_image(void *thread_data)
{
	int						i;
	int						j;
	int						k;
	int						l;
	t_ray					r;
	t_vec3					aim;
	t_vec3					start;
	t_vec3					start2;
	t_vec3					start3;
	t_renderer_thread		*data;
	t_scene					*sce;
	t_vec3					aa[64];
	double					percent_per_line;

	data = (t_renderer_thread*)thread_data;
	sce = data->sce;
	sce->obj = ft_lstdup(sce->obj);
	percent_per_line = (double)sce->cam.w / ((double)sce->cam.w * (double)sce->cam.h);
	sce->cam = camera_set(sce->cam);
	aim = sce->cam.top_left;
	aim = vec3_sub(aim, vec3_mult(data->y_begin, sce->cam.vy));
	aim = vec3_add(aim, vec3_mult(0.5, sce->cam.vy));
	aim = vec3_sub(aim, vec3_mult(0.5, sce->cam.vx));
	r = ray_new(sce->cam.pos, aim);
	i = data->y_begin - 1;
	while (++i < data->y_end)
	{
		start = aim;
		j = -1;
		while (++j < sce->cam.w)
		{
			start2 = aim;
			if (sce->aa != 0)
			{
				k = -1;
				while (++k < sce->aa)
				{
					start3 = aim;
					l = -1;
					while (++l < sce->aa)
					{
						aa[k * sce->aa + l] = ray_trace(sce, r, 0);
						aim = vec3_add(aim, vec3_mult(1. / (double)sce->aa, sce->cam.vx));
						r = ray_new(sce->cam.pos, aim);
					}
					aim = vec3_sub(start3, vec3_mult(1. / (double)sce->aa, sce->cam.vy));
					r = ray_new(sce->cam.pos, aim);
				}
				data->light[i * sce->cam.w + j] = color_average(aa, sce->aa * sce->aa);
			}
			else
				data->light[i * sce->cam.w + j] = ray_trace(sce, r, 0);
			aim = vec3_add(start2, sce->cam.vx);
			r = ray_new(sce->cam.pos, aim);
		}
		aim = vec3_sub(start, sce->cam.vy);
		r = ray_new(sce->cam.pos, aim);

		pthread_mutex_lock(&sce->ui->mutex_stock);
			update_progress_bar(sce, percent_per_line);
		pthread_mutex_unlock(&sce->ui->mutex_stock);
	}
	return (NULL);
}

void			*renderer_compute_image2(void *sce2)
{
	pthread_t			threads[CORE_COUNT];
	t_renderer_thread	threads_data[CORE_COUNT];
	int					i;
	//int					*pixels;
	t_vec3				*light;

	t_scene *sce = (t_scene *)sce2;
	sce->percent = malloc(sizeof(double));
	*sce->percent = 0.;
	*sce->ui->percent = 0.;
	sce->pixels = (int*)malloc(sizeof(int) * sce->cam.w * sce->cam.h);
	light = (t_vec3*)malloc(sizeof(t_vec3) * sce->cam.w * sce->cam.h);
	i = 0;
	while (i < CORE_COUNT)
	{
		threads_data[i].sce = sce;
		threads_data[i].sce = malloc(sizeof(t_scene));
		memcpy(threads_data[i].sce, sce, sizeof(t_scene));
		threads_data[i].pixels = sce->pixels;
		threads_data[i].light = light;
		threads_data[i].y_begin = sce->cam.h / CORE_COUNT * i;
		threads_data[i].y_end = sce->cam.h / CORE_COUNT * (i + 1);
		threads_data[i].y_range = threads_data[i].y_end - threads_data[i].y_begin;
		if (pthread_create(&(threads[i]), NULL, thread_compute_image, &(threads_data[i])))
		{
			perror("renderer: can not create threads");
			exit(0);
		}
		++i;
	}
	i = 0;
	while (i < CORE_COUNT)
	{
		if (pthread_join(threads[i], NULL))
		{
			perror("renderer: can not wait for threads");
			exit(0);
		}
		++i;
	}
	light_to_pixel(light, sce->pixels, sce->cam.w, sce->cam.h);
	free(light);
	*sce->ui->percent = 1.1;
	return (NULL);
}

int		test(void *data)
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

void renderer_compute_image(t_scene *sce)
{
	pthread_t thread;

	sce->ui->rendering = 1;
	pthread_create(&thread, NULL, renderer_compute_image2, sce);
	gdk_threads_add_timeout(100, test, sce);
}
