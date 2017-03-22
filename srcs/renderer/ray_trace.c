#include <math.h>
#include "renderer.h"

/*
** Intersect obj with ray
** - Updates ray->t if smaller distance found
** @return 0 if no collision, 1 if collision
*/
static int		ray_object(t_obj *obj, t_ray *ray)
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
			if (ray->type != OCCLUSION_RAY)
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
	if (collision && ray->type != OCCLUSION_RAY)
	{
		ray->pos = vec3_add(ray->pos, vec3_mult(ray->t - EPS, ray->dir));
		ray->n = ray->collided->normal(ray->collided, ray->pos);
	}
	return (collision);
}

/*
** go to next intersection from regular intersect function
** if collision from outside
**   if object transparent :
**     shoot again
**   else :
**     stop
** if collision from inside :
**   get dist and add absorbance to ray.light
**   shoot again
*/

/*
** Get whole intervals when doing ray_object
** no duct tape needed, it's just duct tape in itself
*/
/*
static t_ray	duct_tape(t_obj *obj, t_ray ray, t_spot spot)
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
			if (ray->type != OCCLUSION_RAY)
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

static t_vec3	rt_shadow(t_scene *sce, t_ray *ray)
{
	t_list		*l;
	int			collision;
	t_obj		*obj;
	t_vec3		absorbance_acc;
	t_vec3		absorbance;

	l = sce->obj;
	collision = 0;
	absorbance_acc = (t_vec3){0, 0, 0};
	absorbance = (t_vec3){0, 0, 0};
	while (l)
	{
		obj = (t_obj*)l->content;
		absorbance = duct_tape(obj, ray);
		absorbance_acc.x *= exp(absorbance.x);
		absorbance_acc.y *= exp(absorbance.y);
		absorbance_acc.z *= exp(absorbance.z);
		l = l->next;
	}
	return (absorbance_acc);
}
*/

static t_vec3	rt_shadow(t_scene *sce, t_ray ray)
{
	t_list		*l;
	t_obj		*obj;
	t_vec3		absorbance;
	double		spot_dist;

	l = sce->obj;
	absorbance = (t_vec3){0, 0, 0};
	spot_dist = ray.t;
	ray.type = OCCLUSION_RAY;
	while (l)
	{
		ray.t = spot_dist;
		obj = (t_obj*)l->content;
		if (ray_object(obj, &ray))
		{
			if (ray.collided->transmittance > 0)
				absorbance = vec3_sub(absorbance,
						vec3_mult(ray.collided->transmittance * ABSORB_COEFF,
									ray.collided->color));
			else
				return (vec3_mult(-BIG_DIST, (t_vec3){1.0, 1.0, 1.0}));
		}
		l = l->next;
	}
	return (absorbance);
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
	t_vec3		absorbance;

	obj_cam = vec3_mult(-1, ray.dir);
	light = color_light_mix(ray.collided->color,
							sce->ambiant.color,
							sce->ambiant.intensity);
	ray.type = ray.type == REFLECTION_RAY ? REFLECTION_RAY : OCCLUSION_RAY;
	absorbance = (t_vec3){0.0, 0.0, 0.0};
	l = sce->spot;
	while (l)
	{
		spot = (t_spot*)l->content;
		ray.dir = vec3_sub(spot->pos, ray.pos);
		ray.t = vec3_norm(ray.dir);
		ray.dir = vec3_mult(1. / ray.t, ray.dir);
		absorbance = vec3_apply(rt_shadow(sce, ray), exp);
		light = vec3_add(light, color_add_light(ray, spot, absorbance, obj_cam));
		l = l->next;
	}
	return (light);
}


t_vec3			ray_trace(t_scene *sce, t_ray ray, int depth)
{
	t_vec3		light;
	t_vec3		refl_light;
	t_ray		new_ray;

	light = (t_vec3){0, 0, 0};
	if (rt_object(sce, &ray))
	{
		ray.dist = ray.dist < 1.0 ? 1.0 : ray.dist + ray.t;
		light = rt_light(sce, ray);
		if (depth < MAX_REC_DEPTH)
		{
			if (ray.collided->reflectance > 0)
			{
				refl_light = ray_trace(sce, reflected_ray(ray), depth + 1);
				light = vec3_add(light, color_light_mix(get_texture_color(ray),
					refl_light,
					REFL_ATTENUATION * ray.collided->reflectance / (ray.dist * (1.0 - ray.collided->transmittance))));
			}
			if (ray.collided->transmittance > 0)
			{
				new_ray = refracted_ray(ray);
				if (new_ray.t > 0)
				{
					refl_light = ray_trace(sce, new_ray, depth + 1);
					light = vec3_add(light, color_light_mix(get_texture_color(ray),
												refl_light,
												ray.collided->transmittance));
				}
			}
		}
	}
	/*
	if (ray.collided)
		free(ray.collided);
		*/
	if (ray.type == REFLECTION_RAY)
		return (vec3_mult(1.0 / ray.dist, light));
	return (light);
}
