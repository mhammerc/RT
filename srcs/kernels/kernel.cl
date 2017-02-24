#include <env.h>

__kernel void compute_color(__global int* pixels)
{
    int     i;

    i = get_global_id(0);
    pixels[i] = 0xff2a002a;
	FLOAT3 x;
	x.xyz = 9.8;
	FLOAT3 y;
	y.xyz = 9.8;
	x *= y;
	pixels[i] = 0xff0000ff * (int)x.x;
}
