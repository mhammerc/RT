#include <env.h>
/*
   int		compute_shaded_color(t_app *app, int color, double shade)
   {
   int		shaded_color;
   double	l;

   l = app->config.ambiant_light;
   shaded_color = (int)((double)(color & 0x0000FF)
 * (l + (1 - l) * shade)) & 0x0000FF;
 shaded_color += (int)((double)(color & 0x00FF00)
 * (l + (1 - l) * shade)) & 0x00FF00;
 shaded_color += (int)((double)(color & 0xFF0000)
 * (l + (1 - l) * shade)) & 0xFF0000;
 return (shaded_color);
 }
 */

/*
int			ft_solve(float a, float b, float c, float *t)
{
	float	delta;
	float	q;
	float	t0;
	float	t1;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	q = (b > 0) ? -0.5 * (b +sqrt(delta)) : -0.5 * (b - sqrt(delta));
	//q = -0.5 * (b +sqrt(delta));
	t0 = q / a;
	t1 = c / q;
	if (t0 > t1)
		*t = t1;
	else
		*t = t0;
	if (*t < 0)
		return (0);
	return (1);
}
*/

int norm_quad_solve(float b, float c, float *t)
{
	float	d;
	float	x1;
	float	x2;
	int		res;

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

int			sphere_intersect(t_obj *self, t_ray *ray)
{
	float	b;
	float	c;
	float3	ray_sphere;

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

float3		sphere_normal(t_obj *self, float3 pos)
{
	return (normalize( pos - self->pos));
}

int			obj_intersect(t_obj *self, t_ray *ray)
{
	if (self->type == SPHERE)
		return (sphere_intersect(self, ray));
	//calls for intersection of other types of object go here
	else
		return (0);
}

float3		obj_normal(t_obj *self, float3 pos)
{
	float3	dummy;

	dummy = {0, 0, 0}
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	//calls for normal of other types of object go here
	else
		return (dummy);
}

/*
** Intersect ray with all objects in scene
** @return 1 if collision, 0 otherwise. ray is updated if collision
*/

int			rt_object(t_obj *obj, int nb_obj, t_ray *ray)
{
	int		collision;
	int		i;

	i = 0;
	collision = 0;
	while (i < nb_obj)
	{
		if (obj_intersect(obj + i), ray)
			collision = 1;
		++i;
	}
	if (ray->type == INITIAL_RAY && collision)
	{
		ray->hit = ray->pos + (ray->d - EPS) * ray->dir;
		ray->n = obj_normal(obj + ray->collided, ray->hit);
	}
	return (collision);
}

float3		color_add_ambiant(float3 obj_color, t_spot ambiant)
{
	return (ambiant.color * obj_color * ambiant.intensity);
	/*
	return ((float3){ambiant.color.x * obj_color.x * ambiant.intensity,
					ambiant.color.y * obj_color.y * ambiant.intensity,
					ambiant.color.z * obj_color.z * ambiant.intensity});
					*/
}

float3		color_add_light(t_ray ray, t_obj obj, t_spot l, float3 obj_cam)
{
	float	diff;
	float3	h;
	float3	light;

	light = 0.0;
	if ((diff = fmax(dot(ray.dir, ray.n), 0)) > 0)
	{
		diff *= obj.kdiff * l.intensity;
		light = l.color * obj.color * diff;
		/*
		light.x += l.color.x * obj.color.x * diff;
		light.y += l.color.y * obj.color.y * diff;
		light.z += l.color.z * obj.color.z * diff;
		*/
	}
	h = normalize(obj_cam + ray.dir);
	if ((diff = fmax(pow(dot(ray.n, h), obj.kp), 0)) > 0)
	{
		diff *= obj.kspec * l.intensity;
		light += l.color * obj.color * diff;
		/*
		light.x += l.color.x * obj.color.x * diff;
		light.y += l.color.y * obj.color.y * diff;
		light.z += l.color.z * obj.color.z * diff;
		*/
	}
	return (light);
}

/*
** Cast a ray to all lights in scene, add in light contribution
** @return light contribution
*/

float3		rt_light(t_obj *obj, int nb_obj,
					t_spot *spot, int nb_spot,
					t_spot ambiant,
					t_ray ray)
{
	float3	obj_cam;
	float3	light;
	int		i;

	i = 0;
	obj_cam = -ray.dir;
	light = color_add_ambiant(obj[ray.collided].color, ambiant);
	ray.type = OCCLUSION_RAY;
	while (i < nb_spot)
	{
		ray.dir = normalize(spot[i].pos - ray.pos);
		if (!rt_object(obj, nb_obj, &ray))
			light += color_add_light(ray, obj[ray.collided], spot[i], obj_cam);
		++i;
	}
	return (light);
}

__kernel void	compute_color(__global float3* light,
								__global t_cl_scene *sce,
								__global t_obj *obj,
								__global t_spot *spot)
{
	int			pos;
	t_ray		ray;
	int			i;
	int			j;

	pos = get_global_id(0);
	j = pos % sce->cam.w;
	i = pos / sce->cam.w;
	ray.pos = sce->cam.pos;
	ray.dir = sce->cam.top_left - i * sce->cam.vy + j * sce->cam.vx - ray.pos;
	ray.n = 0.0;
	ray.t = BIG_DIST + 1;
	ray.type = INITIAL_RAY;
	ray.collided = -1;
	ray.hit = 0.0;
	ray.color = 0.0;

	if (rt_object(obj, sce->nb_obj, t_ray *ray))
		light[pos] = rt_light(obj, sce->nb_obj, spot, sce->nb_spot, sce->ambiant, ray);

	/*
	//test intersectio
	float		t;
	float3		o_c;

	t = 0.;
	o_c = ray.origine - sphere.origine;
	if(ft_solve(dot(ray.dir, ray.dir), 2 * dot((ray).dir, o_c), dot(o_c, o_c) - sphere.size * sphere.size, &t))
	{
		if (t < ray.t)
		{
			ray.t = t;
			ray.hit = ray.origine +  t * ray.dir;


			//determine couleur
			int	cache;
			float3	normal;
			float3	L;
			float3	H;

			normal = ray.hit -  sphere.origine;
			normal = normal / length(normal);
			L = spot.origine -  ray.hit;
			L = L / length(L);
			H = 0.72f * ( L - (ray.dir / length(ray.dir)));
			cache = 1;
			pixels[pos] = 0xff000000 + ((int)(150.f * cache * dot(normal, L) + dot(normal, H)) & 0xff);
		}
		else
			pixels[pos] = 0xffff0000;
	}
	*/
}
