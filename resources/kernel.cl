__kernel void compute_color(__global int* pixels)
{
    int     i;

    i = get_global_id(0);
    pixels[i] = 0xff2a002a;
	float3 x;
	x.xyz = 9.8;
	float3 y;
	y.xyz = 9.8;
	x *= y;
	pixels[i] = 0xff0000ff * (int)x.x;
}
