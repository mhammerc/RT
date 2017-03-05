#include <stdio.h>

#include "renderer.h"
#include "shared.h"

void		opencl_check_error(cl_int error)
{
	if (error != CL_SUCCESS)
	{
		dprintf(2, "OpenCL call failed with error %d\n", error);
		exit(1);
	}
}
