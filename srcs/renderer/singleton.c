#include "renderer.h"

t_scene_manager	*opencl_get()
{
	static t_scene_manager	manager = {};

	return (&manager);
}
