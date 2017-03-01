#include <env.h>

static int		norm_quad_solve(float b, float c, float *t)
{
	float		d;
	float		x1;
	float		x2;
	int			res;

	d = b * b - c;
	if (d < 0.)
		return (0);
	res = 0;
	d = sqrt(d);
	x1 = -b - d;
	x2 = -b + d;
	if (x1 > 0. && x1 < *t)
	{
		res = 1;
		*t = x1;
	}
	if (x2 > 0. && x2 < *t)
	{
		res = 1;
		*t = x2;
	}
	return (res);
}

static int		sphere_intersect(__constant t_obj *self, t_ray *ray)
{
	float		b;
	float		c;
	float3		ray_sphere;

	ray_sphere = ray->pos - self->pos;
	b = dot(ray_sphere, ray->dir);
	c = dot(ray_sphere, ray_sphere) - self->param;
	if (norm_quad_solve(b, c, &(ray->t)))
	{
		if (ray->type == INITIAL_RAY)
			ray->collided = self->id;
		return (1);
	}
	return (0);
}

static float3	sphere_normal(__constant t_obj *self, float3 pos)
{
	return (normalize(pos - self->pos));
}

static int		obj_intersect(__constant t_obj *self, t_ray *ray)
{
	if (self->type == SPHERE)
		return (sphere_intersect(self, ray));
	//calls for intersection of other types of object go here
	else
		return (0);
}

static float3	obj_normal(__constant t_obj *self, float3 pos)
{
	float3		dummy;

	dummy = (float3)(0, 0, 0);
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	//calls for normal of other types of object go here
	else
		return (dummy);
}

static float3		color_add_ambiant(float3 obj_color, t_spot ambiant)
{
	//return (ambiant.color * obj_color * ambiant.intensity);
	return ((float3){ambiant.color.x * obj_color.x * ambiant.intensity,
					ambiant.color.y * obj_color.y * ambiant.intensity,
					ambiant.color.z * obj_color.z * ambiant.intensity});
}

static float3		color_add_light(t_ray ray, t_obj obj, t_spot l, float3 obj_cam)
{
	float	diff;
	float3	h;
	float3	light;

	light = 0.0;
	if ((diff = fmax(dot(ray.dir, ray.n), 0)) > 0)
	{
		diff *= obj.kdiff * l.intensity;
		//light = l.color * obj.color * diff;
		light.x += l.color.x * obj.color.x * diff;
		light.y += l.color.y * obj.color.y * diff;
		light.z += l.color.z * obj.color.z * diff;
	}
	h = normalize(obj_cam + ray.dir);
	if ((diff = fmax(pow(dot(ray.n, h), obj.kp), 0)) > 0)
	{
		diff *= obj.kspec * l.intensity;
		//light += l.color * obj.color * diff;
		light.x += l.color.x * obj.color.x * diff;
		light.y += l.color.y * obj.color.y * diff;
		light.z += l.color.z * obj.color.z * diff;
	}
	return (light);
}

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

static int		rt_object(__constant t_obj *obj, int nb_obj, t_ray *ray)
{
	int			collision;
	int			i;

	i = 0;
	collision = 0;
	while (i < nb_obj)
	{
		if (obj_intersect((obj + i), ray))
			collision = 1;
		++i;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->hit = ray->pos + (ray->t - (float)EPS) * ray->dir;
		ray->n = obj_normal(obj + ray->collided, ray->hit);
	}
	return (collision);
}

/*
** Cast a ray to all lights in scene, add in light contribution
** @return light contribution
*/

static float3	rt_light(__constant t_obj *obj, int nb_obj,
						__constant t_spot *spot, int nb_spot,
						t_spot ambiant,
						t_ray ray)
{
	float3		obj_cam;
	float3		light;
	int			i;

	i = 0;
	obj_cam = -ray.dir;
	light = color_add_ambiant(obj[ray.collided].color, ambiant);
	ray.type = OCCLUSION_RAY;
	while (i < nb_spot)
	{
		ray.dir = normalize(spot[i].pos - ray.pos);
		if (!rt_object(obj, nb_obj, ray))
			light += color_add_light(ray, obj[ray.collided], spot[i], obj_cam);
		++i;
	}
	return (light);
}

__kernel void	compute_color(__global float3* light,
								__constant t_cl_scene *sce,
								__constant t_obj *obj,
								__constant t_spot *spot)
{
	int			pos;
	t_ray		ray;
	int			i;
	int			j;

	/*
  	event_t e = async_work_group_copy(xcopy, x+globalid-localid, GROUP_SIZE, 0);
    wait_group_events(1, &e);
	*/
	pos = get_global_id(0);
	j = pos % sce->cam.w;
	i = pos / sce->cam.w;
	ray.pos = sce->cam.pos;
	ray.dir = normalize(sce->cam.top_left - (float)i * sce->cam.vy + (float)j * sce->cam.vx - ray.pos);
	ray.n = 0.0;
	ray.t = BIG_DIST + 1;
	ray.type = INITIAL_RAY;
	//ray.type = OCCLUSION_RAY;
	ray.collided = 0;
	ray.hit = 0.0;
	ray.color = 0.0;

	/*
	light[pos].x = ray.dir.x;
	light[pos].y = ray.dir.y;
	light[pos].z = ray.dir.z;
	*/
	
	if (rt_object(obj, sce->nb_obj, &ray))
		light[pos] = rt_light(obj, sce->nb_obj, spot, sce->nb_spot, sce->ambiant, ray);
	/*
	{

		light[pos].x = 1.0 / ray.t;
		light[pos].y = 1.0 / ray.t;
		light[pos].z = 1.0 / ray.t;
	}
	*/
}
