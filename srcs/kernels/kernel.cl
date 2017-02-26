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
int	ft_solve(float a, float b, float c, float *t)
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
	if(*t < 0)
		return (0);
	return (1);
}

int			norm_quad_solve(float b, float c, float *t)
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

INT			sphere_intersect(t_obj *self, t_ray *ray)
{
	FLOAT	b;
	FLOAT	c;
	FLOAT3	ray_sphere;

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

FLOAT3		sphere_normal(t_obj *self, FLOAT3 pos)
{
	return (normalize( pos - self->pos));
}

INT			obj_intersect(t_obj *self, t_ray *ray)
{
	if (self->type == SPHERE)
		return (sphere_intersect(self, ray));
	//calls for intersection of other types of object go here
	else
		return (0);
}

FLOAT3		obj_normal(t_obj *self, FLOAT3 pos)
{
	FLOAT3	dummy;

	dummy = {0, 0, 0}
	if (self->type == SPHERE)
		return (sphere_normal(self, pos));
	//calls for normal of other types of object go here
	else
		return (dummy);
}

INT			rt_object(t_obj *obj, INT nb_obj, t_ray *ray)
{
	INT		collision;
	INT		i;

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
		ray->n = obj_normal(obj + ray->id, ray->hit);
	}
	return (collision);
}

void		color_add_ambiant(float3 *c, float3 obj_color, t_spot ambiant)
{
	c->x += ambiant.color.x * obj_color.x * ambiant.intensity;
	c->y += ambiant.color.y * obj_color.y * ambiant.intensity;
	c->z += ambiant.color.z * obj_color.z * ambiant.intensity;
}

void		color_add_light(t_ray *ray, t_obj obj, t_spot l, float3 obj_cam)
{
	float	diff;
	float3	h;

	if ((diff = fmax(dot(ray->dir, ray.n), 0)) > 0)
	{
		diff *= obj.kdiff * l->intensity;
		ray->color.x += l.color.x * obj.color.x * diff;
		ray->color.y += l.color.y * obj.color.y * diff;
		ray->color.z += l.color.z * obj.color.z * diff;
	}
	h = normalize(obj_cam + ray.dir);
	if ((diff = fmax(pow(dot(ray->n, h), obj.kp), 0)) > 0)
	{
		diff *= obj.kspec * l->intensity;
		ray->color.x += l.color.x * obj.color.x * diff;
		ray->color.y += l.color.y * obj.color.y * diff;
		ray->color.z += l.color.z * obj.color.z * diff;
	}
}

void		rt_light(t_obj *obj,
					int nb_obj,
					t_spot *spot,
					int nb_spot,
					t_spot ambiant,
					t_ray *ray)
{
	float3	obj_cam;
	int		i;

	i = 0;
	obj_cam = -1.0 * ray.dir;
	color_add_ambiant(&(ray->color), obj[ray.collided].color, ambiant);
	ray.type = OCCLUSION_RAY;
	while (i < nb_spot)
	{
		ray.dir = normalize(spot[i].pos - ray.pos);
		if (!rt_object(obj, nb_obj, &ray))
			color_add_light(ray, obj[ray->collided], spot[i], obj_cam);
		++i;
	}
}

__kernel void compute_color(__global int* pixels,
							__global t_cl_scene *sce,
							__global t_obj *obj,
							__global t_spot *spot)
{
	int		pos;

//ce qu il faudra passer en parametre

	/*
	t_obj	sphere;
	sphere.origine.xy=0;
	sphere.origine.z=-20;
	sphere.size=4;
	sphere.col=150;

	t_spot spot;
	spot.origine.xyz=0;
	*/

    pos = get_global_id(0);

//init ray
	t_ray	ray;
	int	i;
	int	j;

	j = pos % sce.cam.w;
	i = pos / sce.cam.w;
	ray.pos = sce.cam.pos;
	ray.dir = sce.cam.top_left - i * scene.cam.vy + j * scene.cam.vx - ray.pos;
	ray.t = BIG_DIST;

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
}
