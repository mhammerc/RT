#include "ui.h"
#include "renderer.h"
#include "shared.h"

void		anti_aliasing(t_vec2i i,
		t_vec3 a, t_scene *c, t_renderer_thread *data)
{
	int		k;
	int		l;
	t_vec3	s;
	t_vec3	aa[64];

	if (c->aa != 0)
	{
		k = -1;
		while (++k < c->aa)
		{
			s = a;
			l = -1;
			while (++l < c->aa)
			{
				aa[k * c->aa + l] = ray_trace(c, i.r, 0);
				a = vec3_add(a, vec3_mult(1. / (double)c->aa, c->cam.vx));
				i.r = ray_new(c->cam.pos, a);
			}
			a = vec3_sub(s, vec3_mult(1. / (double)c->aa, c->cam.vy));
			i.r = ray_new(c->cam.pos, a);
		}
		data->light[i.x * c->cam.w + i.y] = color_average(aa, c->aa * c->aa);
	}
	else
		data->light[i.x * c->cam.w + i.y] = ray_trace(c, i.r, 0);
}

void		pixel_loop(t_vec2i i, t_vec3 aim, t_scene *sce,
		t_renderer_thread *data)
{
	t_vec3	start;
	t_vec3	start2;
	double	percent_per_line;

	percent_per_line = (double)sce->cam.w / ((double)sce->cam.w
				* (double)sce->cam.h);
	while (++i.x < data->y_end)
	{
		start = aim;
		i.y = -1;
		while (++i.y < sce->cam.w)
		{
			start2 = aim;
			anti_aliasing(i, aim, sce, data);
			aim = vec3_add(start2, sce->cam.vx);
			i.r = ray_new(sce->cam.pos, aim);
		}
		aim = vec3_sub(start, sce->cam.vy);
		i.r = ray_new(sce->cam.pos, aim);
		pthread_mutex_lock(&sce->ui->mutex_stock);
		update_progress_bar(sce, percent_per_line);
		pthread_mutex_unlock(&sce->ui->mutex_stock);
	}
}

void		*thread_compute_image(void *thread_data)
{
	t_vec2i					i;
	t_renderer_thread		*data;
	t_scene					*sce;
	t_vec3					aim;

	data = (t_renderer_thread*)thread_data;
	sce = data->sce;
	sce->obj = ft_lstdup(sce->obj);
	sce->cam = camera_set(sce->cam);
	aim = sce->cam.top_left;
	aim = vec3_sub(aim, vec3_mult(data->y_begin, sce->cam.vy));
	aim = vec3_add(aim, vec3_mult(0.5, sce->cam.vy));
	aim = vec3_sub(aim, vec3_mult(0.5, sce->cam.vx));
	i.r = ray_new(sce->cam.pos, aim);
	i.x = data->y_begin - 1;
	pixel_loop(i, aim, sce, data);
	lstfree(sce->obj);
	return (NULL);
}
