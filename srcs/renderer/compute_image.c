#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "ui.h"
#include "renderer.h"
#include "shared.h"
#include "texture_loader.h"

static t_vec3	tex_spherical_damier(t_ray ray)
{
	t_vec3	d;
	double u;
	double v;

	d = vec3_get_normalized(vec3_sub(ray.collided->pos, ray.pos));
	u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	u = fmod(u, 0.10);
	v = 0.5 - asin(d.y) / M_PI;
	v = fmod(v, 0.10);
	if (u < 0.05 && v < 0.05)
		return (BLACK);
	if (u > 0.05 && v < 0.05)
		return (WHITE);
	if (u > 0.05 && v > 0.05)
		return (BLACK);
	if (u < 0.05 && v > 0.05)
		return (WHITE);
	return (WHITE);
}

static t_vec3	tex_spherical(t_ray ray)
{
	t_vec3	r;
	t_vec3	d;
	double	u;
	double	v;

	d = vec3_get_normalized(vec3_sub(ray.collided->pos, ray.pos));
	u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	u *= ray.collided->texture.width;
	v = 0.5 - asin(d.y) / M_PI;
	v *= ray.collided->texture.height;
	int offset = 3;
	if (ray.collided->texture.has_alpha)
		offset = 4;
	r.x = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride];
	r.y = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride + 1];
	r.z = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride + 2];
	r = vec3_mult(1. / 256., r);
	return (r);
}

t_vec3			get_texture_color(t_ray ray)
{
	t_vec3	r;
	t_vec3	d;
	double	u;
	double	v;

	if (ray.collided->have_texture == NO_TEXTURE)
		return (ray.collided->color);
	else if (ray.collided->have_texture == SPHERICAL_DAMIER)
		return (tex_spherical_damier(ray));
	else if (ray.collided->have_texture == SPHERICAL
			&& ray.collided->texture.is_valid)
		return (tex_spherical(ray));
	else if (ray.collided->have_texture == PLANAR
			&& ray.collided->texture.is_valid)
	{
		d = vec3_sub(ray.collided->pos, ray.pos);
		t_vec3	tmp;
		tmp = vec3_cross(d, ray.collided->dir);
		if (fabs(ray.collided->dir.x) < fabs(ray.collided->dir.y))
		{
			u = d.x;
			v = tmp.x;
		}
		else
		{
			u = d.y;
			v = tmp.y;
		}
		if (u < 0.)
			u = -u;
		if (v < 0.)
			v = -v;
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);
		u *= ray.collided->texture.width;
		v *= ray.collided->texture.height;
		int offset = 3;
		if (ray.collided->texture.has_alpha)
			offset = 4;

		r.x = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride];
		r.y = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride + 1];
		r.z = ray.collided->texture.pixels[(int)u * offset + (int)v * ray.collided->texture.rowstride + 2];
		r = vec3_mult(1. / 256., r);
		return (r);
	}
	else if (ray.collided->have_texture == PLANAR_DAMIER)
	{
		d = vec3_sub(ray.collided->pos, ray.pos);
		t_vec3	tmp;
		tmp = vec3_cross(d, ray.collided->dir);
		if (fabs(ray.collided->dir.x) < fabs(ray.collided->dir.y))
		{
			u = d.x;
			v = tmp.x;
		}
		else
		{
			u = d.y;
			v = tmp.y;
		}
		if (u < 0.)
		{
			u -= 0.5;
			u = -u;
		}
		if (v < 0.)
		{
			v -= 0.5;
			v = -v;
		}
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);
		if (u < 0.5 && v < 0.5)
			return (BLACK);
		if (u > 0.5 && v < 0.5)
			return (WHITE);
		if (u > 0.5 && v > 0.5)
			return (BLACK);
		if (u < 0.5 && v > 0.5)
			return (WHITE);
		return (WHITE);
	}
	else
		return (ray.collided->color);
}

void			filter_black_and_white(t_vec3 *light, int len)
{
	int		i;
	double	tmp2;

	i = -1;
	while (++i < len)
	{
		tmp2 = light[i].x + light[i].y + light[i].z;
		tmp2 /= 3;
		light[i].x = tmp2;
		light[i].y = tmp2;
		light[i].z = tmp2;
	}

}

void			filter_sepia(t_vec3 *light, int len)
{
	int		i;
	t_vec3	tmp;

	i = -1;
	while (++i < len)
	{
		tmp.x = (light[i].x * .393) + (light[i].y * .769) + (light[i].z * .189);
		tmp.y = (light[i].x * .349) + (light[i].y * .686) + (light[i].z * .168);
		tmp.z = (light[i].x * .272) + (light[i].y * .534) + (light[i].z * .131);
		light[i] = tmp;
	}
}

static void 	light_apply_filters(t_scene *sce, t_vec3 *light, int w, int h)
{
	int		len;

	len = w * h;
	if (sce->filter == BLACK_WHITE)
		filter_black_and_white(light, len);
	if (sce->filter == SEPIA)
		filter_sepia(light, len);
}

static void		update_progress_bar(t_scene *scene, double percent_per_line)
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

void			lstfree(t_list	*begin)
{
	t_list	*list;
	t_list	*tmp;
	t_obj	*obj;

	list = begin;
	while (list)
	{
		obj = (t_obj*)list->content;
		if (obj->type == POLYGONS && obj->faces)
		free(obj->faces);
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
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
	lstfree(sce->obj);
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
		threads_data[i].sce = malloc(sizeof(t_scene));
		ft_memcpy(threads_data[i].sce, sce, sizeof(t_scene));
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
	light_apply_filters(sce, light, sce->cam.w, sce->cam.h);
	light_to_pixel(light, sce->pixels, sce->cam.w, sce->cam.h);
	free(light);
	i = 0;
	while (i < CORE_COUNT)
	{
		free(threads_data[i].sce);
		++i;
	}
	free(sce->percent);
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
	pthread_detach(thread);
	gdk_threads_add_timeout(100, test, sce);
}
