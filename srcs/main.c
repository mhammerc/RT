#include "rt.h"
#include <gtk/gtk.h>

int			main(int argc, char **argv)
{
	opencl_init();
	interface_init(argc, argv);

	return (0);
}


