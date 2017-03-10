void	ft_start_ray(__global char *data, __global t_env *e, int x, int y)
{
	int i;
	int j;
	int4	pixel_tab[e->mlx->crenelage * e->mlx->crenelage];
	int4 pixel;
	int n;
	__global char	*pos;

	i = 0;
	
	while (i < e->mlx->crenelage)
	{
		j = 0;
		while (j < e->mlx->crenelage)
		{
			pixel.x = 0;
			pixel.y = 0;
			pixel.z = 0;
			pixel_tab[i * e->mlx->crenelage + j] = ft_raytracer(x * e->mlx->crenelage + i, y * e->mlx->crenelage + j, e, pixel);
			j++;
		}
		i++;
	}
	pixel.x = 0;
	pixel.y = 0;
	pixel.z = 0;
	n = 0;
	while (n < e->mlx->crenelage * e->mlx->crenelage)
	{
		pixel.x += pixel_tab[n].x;
		pixel.y += pixel_tab[n].y;
		pixel.z += pixel_tab[n].z;
		n++;
	}
	pos = data + y * e->mlx->sizeline + e->mlx->bpp / 8 * x;
	*pos = pixel.x / (e->mlx->crenelage * e->mlx->crenelage);
	*(pos + 1) = pixel.y / (e->mlx->crenelage * e->mlx->crenelage);
	*(pos + 2) = pixel.z / (e->mlx->crenelage * e->mlx->crenelage);

}

__kernel void	ft_start_calc(__global char *data, __global t_obj *obj, __global t_light *light, __global t_env *e, __global t_mlx *mlx, __global t_cam *cam)
{
	int x;
	int y;

	y = get_global_id(0);
	e[y].l_obj = obj;
	e[y].light = light;
	e[y].mlx = mlx;
	e[y].cam = cam;
	mlx->crenelage = 1;
	x = 0;
	while (x < mlx->w)
	{
		ft_start_ray(data, &e[y], x, y);
		x++;
	}
}
