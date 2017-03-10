int4			put_pixel(int x, int y, __global t_env *e)
{
	int4 pixel;
	pixel.x = (unsigned char)e->b;
	pixel.y = (unsigned char)e->g;
	pixel.z = (unsigned char)e->r;
	return (pixel);
}
