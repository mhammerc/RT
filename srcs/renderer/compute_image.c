#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "ui.h"
#include "renderer.h"
#include "shared.h"

float			light_find_max(t_renderer_thread *data)
{
	float		max;
	int			i;
	int			len;

	len = data->sce->cam.w * data->y_begin + data->sce->cam.w * data->y_range;
	max = 0.;
	i = data->sce->cam.w * data->y_begin - 1;
	while (++i < len)
	{
		max = fmax(max, data->light[i].x);
		max = fmax(max, data->light[i].y);
		max = fmax(max, data->light[i].z);
	}
	return (max);
}

int				colorcomp_to_rgb(int r, int g, int b)
{
	r = r < 0 ? 0 : (r & 0xff);
	g = g < 0 ? 0 : (g & 0xff);
	b = b < 0 ? 0 : (b & 0xff);
	return ((0xff << ALPHA_BITSHIFT) + (r << R_BITSHIFT) + (g << G_BITSHIFT) + (b << B_BITSHIFT));
}

//void			light_to_pixel(t_vec3 *light, int *px, int w, int h)
void			light_to_pixel(t_renderer_thread *data)
{
	float		invmax;
	int			i;
	int			len;

	len = data->sce->cam.w * data->y_begin + data->sce->cam.w * data->y_range;
	invmax = 255. / light_find_max(data);
	i = data->sce->cam.w * data->y_begin - 1;
	while (++i < len)
	{
		data->pixels[i] = colorcomp_to_rgb(data->light[i].x * invmax,
									data->light[i].y * invmax,
									data->light[i].z * invmax);
	}
}

/*
** Add color components
*/

t_vec3		color_add_light(t_ray ray, t_spot *l, t_vec3 obj_cam)
{
	t_vec3	obj;
	t_vec3	light;
	double	diff;
	t_vec3	h;

	light = (t_vec3){0, 0, 0};
	obj = ray.collided->color;
	if ((diff = fmax(vec3_dot(ray.dir, ray.n), 0)) > 0)
	{
		diff *= ray.collided->kdiff * l->intensity;
		light.x = l->color.x * obj.x * diff;
		light.y = l->color.y * obj.y * diff;
		light.z = l->color.z * obj.z * diff;
	}
	h = vec3_get_normalized(vec3_add(obj_cam, ray.dir));
	if ((diff = fmax(pow(vec3_dot(ray.n, h), ray.collided->kp), 0)) > 0)
	{
		diff *= ray.collided->kspec * l->intensity;
		light.x += l->color.x * obj.x * diff;
		light.y += l->color.y * obj.y * diff;
		light.z += l->color.z * obj.z * diff;
	}
	return (light);
}

t_vec3		color_add_ambiant(t_vec3 obj, t_spot ambiant)
{
	t_vec3	light;

	light = (t_vec3){0, 0, 0};
	light.x = ambiant.color.x * obj.x * ambiant.intensity;
	light.y = ambiant.color.y * obj.y * ambiant.intensity;
	light.z = ambiant.color.z * obj.z * ambiant.intensity;
	return (light);
}

/*
** Ray constructor
** @return a new ray
*/

t_ray		ray_new_aim(t_vec3 pos, t_vec3 aim)
{
	t_vec3	dir;
	t_vec3	n;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, BIG_DIST + 1,  INITIAL_RAY, NULL, n, n});
}

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

static int		rt_object(t_scene *sce, t_ray *ray)
{
	t_list		*l;
	int			collision;
	t_obj		*obj;

	l = sce->obj;
	collision = 0;
	while (l)
	{
		obj = (t_obj*)l->content;
		if (obj->intersect(obj, ray))
			collision = 1;
		l = l->next;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->pos = vec3_add(ray->pos, vec3_mult(ray->t - EPS, ray->dir));
		ray->n = ray->collided->normal(ray->collided, ray->pos);
	}
	return (collision);
}

/*
** Cast a ray to all lights in scene, accumulate light contributions
** @return light contribution as a t_vec3
*/

static t_vec3	rt_light(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_vec3		obj_cam;
	t_vec3		light;
	t_spot		*spot;

	obj_cam = vec3_mult(-1, ray.dir);
	light = color_add_ambiant(ray.collided->color, sce->ambiant);
	ray.type = OCCLUSION_RAY;
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		if (!rt_object(sce, &ray))
			light = vec3_add(light, color_add_light(ray, spot, obj_cam));
		l = l->next;
	}
	return (light);
}

static t_vec3	ray_trace(t_scene *sce, t_ray ray)
{
	t_vec3		light;

	light = (t_vec3){0, 0, 0};
	if (rt_object(sce, &ray))
		light = rt_light(sce, ray);
	return (light);
}

static void		*thread_compute_image(void *thread_data)
{
	int					i;
	int					j;
	t_ray				r;
	t_vec3				aim;
	t_vec3				start;
	t_renderer_thread	*data;
	t_scene				*sce;

	data = (t_renderer_thread*)thread_data;
	sce = data->sce;
	sce->cam = camera_set(sce->cam);
	aim = sce->cam.top_left;
	aim = vec3_sub(aim, vec3_mult(data->y_begin, sce->cam.vy));
	r = ray_new_aim(sce->cam.pos, aim);
	i = data->y_begin - 1;
	while (++i < data->y_end)
	{
		start = aim;
		j = -1;
		while (++j < sce->cam.w)
		{
			data->light[i * sce->cam.w + j] = ray_trace(sce, r);
			aim = vec3_add(aim, sce->cam.vx);
			r = ray_new_aim(sce->cam.pos, aim);
		}
		aim = vec3_sub(start, sce->cam.vy);
		r = ray_new_aim(sce->cam.pos, aim);
	}
	light_to_pixel(data);
	return (NULL);
}

void			renderer_compute_image(t_scene *sce)
{
	pthread_t			threads[CORE_COUNT];
	t_renderer_thread	threads_data[CORE_COUNT];
	int					i;
	int					*pixels;
	t_vec3				*light;

	pixels = (int*)ft_memalloc(sizeof(int) * sce->cam.w * sce->cam.h);
	light = (t_vec3*)ft_memalloc(sizeof(t_vec3) * sce->cam.w * sce->cam.h);
	i = 0;
	while (i < CORE_COUNT)
	{
		threads_data[i].sce = sce;
		threads_data[i].pixels = pixels;
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
	ui_print_scene(pixels);
	free(pixels);
}
