#include <stdio.h>
#include <strings.h>
#include <math.h>

#include "renderer.h"
#include "shared.h"

float			light_find_max(int w, int h, t_vec3 *light)
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
{
	float		invmax;
	int			i;
	int			len;

	len = w * h;
	invmax = 255. / light_find_max(w, h, light);
	i = -1;
	while (++i < len)
	{
		px[i] = colorcomp_to_rgb(light[i].x * invmax,
									light[i].y * invmax,
									light[i].z * invmax);
	}
	return ;
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

int				*renderer_compute_image(t_scene *sce)
{
	int					*pixels;
	t_vec3				*light;
	int					i;
	int					j;
	t_ray				r;
	t_vec3				aim;
	t_vec3				start;

	sce->cam = camera_set(sce->cam);
	obj = sce->obj;
	spot = sce->light;

	pixels = (int*)ft_memalloc(sizeof(int) * scene->cam.w * scene->cam.h);
	light = (t_vec3*)ft_memalloc(sizeof(t_vec3) * scene->cam.w * scene->cam.h);
	if (NULL == pixels || NULL == light)
		exit(EXIT_FAILURE);

	//lance le kernel
	aim = sce->cam->top_left;
	r = ray_new_aim(sce->cam->pos, aim, light);
	i = -1;
	while (++i < e->h)
	{
		start = aim;
		j = -1;
		while (++j < e->w)
		{
			if (rt_object(sce, &r))
				rt_light(sce, r);
			aim = vec3_add(aim, sce->cam->vx);
			r = ray_new_aim(sce->cam->pos, aim, r.light + 1);
		}
		aim = vec3_sub(start, e->sce->cam->vy);
		r = ray_new_aim(sce->cam->pos, aim, r.light);
	}
	light_to_pixel(light, pixels, sce->cam.w, sce->cam.h);
	printf("New image rendered.\n");
	return (pixels);
}
