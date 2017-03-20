#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "ui.h"
#include "renderer.h"
#include "shared.h"

float			light_find_max(t_vec3 *light, int w, int h)
{
	float		max;
	int			i;
	int			len;

	len = w * h;
	max = 0.;
	i = -1;
	while (++i < len)
	{
		max = fmax(max, light[i].x);
		max = fmax(max, light[i].y);
		max = fmax(max, light[i].z);
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

void			light_to_pixel(t_vec3 *light, int *px, int w, int h)
//void			light_to_pixel(t_renderer_thread *data)
{
	float		invmax;
	int			i;
	int			len;

	len = w * h;
	invmax = 255. / light_find_max(light, w, h);
	i = -1;
	while (++i < len)
	{
		px[i] = colorcomp_to_rgb(light[i].x * invmax,
									light[i].y * invmax,
									light[i].z * invmax);
	}
}

/*
** Add color components
*/
t_vec3		color_light_mix(t_vec3 obj_color, t_vec3 light_color, double coeff)
{
	t_vec3	res;

	res.x = obj_color.x * light_color.x * coeff;
	res.y = obj_color.y * light_color.y * coeff;
	res.z = obj_color.z * light_color.z * coeff;
	return (res);
}

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
		light = color_light_mix(obj, l->color, diff);
	}
	h = vec3_get_normalized(vec3_add(obj_cam, ray.dir));
	if ((diff = fmax(pow(vec3_dot(ray.n, h), ray.collided->kp), 0)) > 0)
	{
		diff *= ray.collided->kspec * l->intensity;
		light = vec3_add(light, color_light_mix(obj, l->color, diff));
	}
	return (light);
}

/*
** Ray constructor
** @return a new ray
*/

t_ray		ray_new_aim(t_vec3 pos, t_vec3 aim)
{
	t_vec3	n;
	t_vec3	dir;

	n = (t_vec3){0, 0, 0};
	dir = vec3_get_normalized(vec3_sub(aim, pos));
	return ((t_ray){pos, dir, n, BIG_DIST + 1,  INITIAL_RAY, NULL, n, n});
}

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/
static int		ray_object(t_obj* obj, t_ray *ray)
{
	t_interval	interval;
	int			res;
	t_obj		*collided;

	collided = NULL;
	res = LOCATION_NONE;
	if (obj->intersect(obj, ray, &interval))
	{
		if ((res = minimal_positiv(&interval, obj, &(ray->t), &collided)))
		{
			if (ray->type == INITIAL_RAY)
				ray->collided = collided;
		}
	}
	return (res == LOCATION_NONE ? 0 : 1);
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
		if (ray_object(obj, ray))
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
	light = color_light_mix(ray.collided->color,
							sce->ambiant.color,
							sce->ambiant.intensity);
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

static t_ray	reflected_ray(t_ray ray)
{
	t_vec3	refl;

	refl = vec3_mult(-1, ray.dir);
	refl = vec3_add(ray.pos, vec3_mult(2 * vec3_dot(ray.n, refl), ray.n));
	refl = vec3_add(refl, ray.dir);
	ray = ray_new_aim(ray.pos, refl);
	return (ray);
}

static t_vec3	ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;
	t_vec3		refl_light;

	light = (t_vec3){0, 0, 0};
	if (depth > MAX_REC_DEPTH)
		return (light);
	if (rt_object(sce, &ray))
	{
		light = rt_light(sce, ray);
		if (ray.collided->kspec > 0)
		{
			refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
			refl_light = vec3_mult(REFL_ATTENUATION, refl_light);
			light = vec3_add(light, color_light_mix(ray.collided->color,
													refl_light,
													ray.collided->kspec));
		}
	}
	return (light);
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

static t_vec3	color_average(t_vec3 *aa, int size)
{
	t_vec3	r;
	int		i;

	r.x = 0.;
	r.y = 0.;
	r.z = 0.;
	i = 0;
	while (i < size)
	{
		r.x += aa[i].x;
		r.y += aa[i].y;
		r.z += aa[i].z;
		++i;
	}
	r.x /= (double)size;
	r.y /= (double)size;
	r.z /= (double)size;
	return (r);
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
	r = ray_new_aim(sce->cam.pos, aim);
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
						r = ray_new_aim(sce->cam.pos, aim);
					}
					aim = vec3_sub(start3, vec3_mult(1. / (double)sce->aa, sce->cam.vy));
					r = ray_new_aim(sce->cam.pos, aim);
				}
				data->light[i * sce->cam.w + j] = color_average(aa, sce->aa * sce->aa);
			}
			else
				data->light[i * sce->cam.w + j] = ray_trace(sce, r, 0);
			aim = vec3_add(start2, sce->cam.vx);
			r = ray_new_aim(sce->cam.pos, aim);
		}
		aim = vec3_sub(start, sce->cam.vy);
		r = ray_new_aim(sce->cam.pos, aim);

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
