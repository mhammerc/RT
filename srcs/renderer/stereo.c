#include "renderer.h"

void		stereo_camera(t_scene *sce, t_cam *cam_left, t_cam *cam_right)
{
	t_cam	cam;
	double	ied;

	ied = IED;
	cam = camera_set(sce->cam);
	*cam_left = sce->cam;
	*cam_right = sce->cam;
	cam_left->pos = vec3_add(cam.pos, vec3_mult(-0.5 * ied, cam.vx));
	cam_right->pos = vec3_add(cam.pos, vec3_mult(0.5 * ied, cam.vx));
	cam_left->dir = vec3_add(cam.dir, vec3_mult(-0.5 * ied, cam.vx));
	cam_right->dir = vec3_add(cam.dir, vec3_mult(0.5 * ied, cam.vx));
}

void		stereo_store_first_cam_pixels(t_scene *sce)
{
	int		*px;
	int		*px2;
	int		size;

	size = sce->cam.w * sce->cam.h;
	px = sce->pixels;
	px2 = sce->pixels + size;
	while (size--)
		*px2++ = *px++;
}

void		stereo_join_cam_pixels(t_scene *sce)
{
	int		*px;
	int		*px2;
	int		size;
	int		red_mask;

	red_mask = RED_MASK;
	size = sce->cam.w * sce->cam.h;
	px = sce->pixels;
	px2 = sce->pixels + size;
	while (size--)
	{
		*px = (*px2++ & ~red_mask) | (*px & red_mask);
		++px;
	}
}
