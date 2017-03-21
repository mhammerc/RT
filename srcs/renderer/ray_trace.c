#include "renderer.h"

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/
static int		ray_object(t_obj* obj, t_ray *ray)
{
	t_interval	interval;
	int			location;
	t_obj		*collided;

	collided = NULL;
	location = LOCATION_NONE;
	if (obj->intersect(obj, ray, &interval))
	{
		collided = (t_obj*)malloc(sizeof(t_obj));
		if ((location = minimal_positiv(&interval, obj, &(ray->t), &collided)))
		{
			if (ray->type == INITIAL_RAY)
			{
				if (ray->collided)
					free(ray->collided);
				ray->collided = collided;
				ray->location = location;
			}
			else
				free(collided);
		}
		else
			free(collided);
	}
	return (location == LOCATION_NONE ? 0 : 1);
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


t_vec3			ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;
	t_vec3		refl_light;
	t_ray		new_ray;
	double		atten;

	light = (t_vec3){0, 0, 0};
	atten = 1.0;
	if (rt_object(sce, &ray))
	{
		ray.dist = ray.dist < 1.0 ? 1.0 : ray.dist + ray.t;
		atten = 1.0 / ray.dist;
		if (atten < EPS)
			return ((t_vec3){0, 0, 0});
		light = rt_light(sce, ray);
		if (depth < MAX_REC_DEPTH)
		{
			if (ray.collided->kspec > 0)
			{
				refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
				refl_light = vec3_mult(REFL_ATTENUATION, refl_light);
				light = vec3_add(light, color_light_mix(get_texture_color(ray),
							refl_light,
							ray.collided->kspec));
			}
			if (ray.collided->transparency > 0)
			{
				new_ray = refracted_ray(ray);
				if (new_ray.t > 0)
				{
					refl_light = ray_trace(sce, new_ray, depth + 1);
					/*
					light = vec3_add(light, color_light_mix((t_vec3){1, 1, 1},
								refl_light,
								ray.collided->transparency));
					*/
					light = vec3_add(light, refl_light);

				}
			}
		}
	}
	if (ray.collided)
		free(ray.collided);
	return (vec3_mult(atten,light));
}
