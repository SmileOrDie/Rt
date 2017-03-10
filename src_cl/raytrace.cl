// void			ft_create_tab_transp(__global t_env *e, t_obj obj, double tr)
// {
// 	int			x;
// 	int			y;
// 	t_obj		*tab;

// 	x = 0;
// 	y = 0;
// 	e->flag ? tab = e->tab_transp_l : (tab = e->tab_transp);
// 	while (tab[x].t != -1 && tab[x].t <= tr)
// 		x++;
// 	while (tab[y].t != -1)
// 		y++;
// 	y++;
// 	while (y > x)
// 	{
// 		tab[y] = tab[y - 1];
// 		y--;
// 	}
// 	tab[x] = obj;
// 	tab[x].t = tr;
// }

void			ft_create_tab_transp(__global t_env *e, t_obj obj, double tr)
{
	int			x;
	int			y;
	t_obj		*tab;

	x = 0;
	y = 0;
	if (e->flag)
	{
		while (e->tab_transp_l[x].t != -1 && e->tab_transp_l[x].t <= tr)
			x++;
		while (e->tab_transp_l[y].t != -1)
			y++;
		y++;
		while (y > x)
		{
			e->tab_transp_l[y] = e->tab_transp_l[y - 1];
			y--;
		}
		e->tab_transp_l[x] = obj;
		e->tab_transp_l[x].t = tr;
	}
	else
	{
		while (e->tab_transp[x].t != -1 && e->tab_transp[x].t <= tr)
		{
			x++;
		}
		while (e->tab_transp[y].t != -1)
		{
			y++;
		}
		y++;
		while (y > x)
		{
			e->tab_transp[y] = e->tab_transp[y - 1];
			y--;
		}
		e->tab_transp[x] = obj;
		e->tab_transp[x].t = tr;
	}
}

void	inter_obj(__global t_env *e, double4 pos, double4 dir)
{
	double		tr;
	int			i;

	i = 0;
	while (i < e->nb_obj)
	{
		if (e->l_obj[i].type == 1)
		{
			if ((tr = inter_sphere(e->l_obj[i], pos, dir)) >= 0)
			{
				ft_create_tab_transp(e, e->l_obj[i], tr);
				;
			}
		}
		else if (e->l_obj[i].type == 2)
		{
			if ((tr = inter_plane(e->l_obj[i], pos, dir)) >= 0)
			{
				ft_create_tab_transp(e, e->l_obj[i], tr);
				;
			}
		}
		else if (e->l_obj[i].type == 3)
		{
			if ((tr = inter_cylinder(e->l_obj[i], pos, dir)) >= 0)
			{
				ft_create_tab_transp(e, e->l_obj[i], tr);
				;
			}
		}
		else if (e->l_obj[i].type == 4)
		{
			if ((tr = inter_cone(e->l_obj[i], pos, dir)) >= 0)
			{
				ft_create_tab_transp(e, e->l_obj[i], tr);
				;
			}
		}
		i++;
	}
}

int4		l_color(int4 c, int4 color, __global t_env *e)
{
	double tmp;

	tmp = pow(ft_clamp(e->angle, 0, 1), 150) * 255;
	(c.x > e->c_hit.x) ? c.x = e->c_hit.x : 0;
	(c.y > e->c_hit.y) ? c.y = e->c_hit.y : 0;
	(c.z > e->c_hit.z) ? c.z = e->c_hit.z : 0;
	c.x += tmp * color.x / 255;
	c.y += tmp * color.y / 255;
	c.z += tmp * color.z / 255;
	(c.x > 255) ? c.x = 255 : 0;
	(c.y > 255) ? c.y = 255 : 0;
	(c.z > 255) ? c.z = 255 : 0;
	return (c);
}

int4		add_light(__global t_env *e, double t, double4 phit, int ct, int4 c)
{
	double4	dir_l;
	double transp;
	int count;
	int4 color;
	int i;
	t_obj tab_transp_l[e->nb_obj + 1];

	e->tab_transp_l = tab_transp_l;
	e->flag = 1;
	i = 0;
	while (i < e->nb_light)
	{
		dir_l = vsub(phit, e->light[i].pos);
		t = sqrt(dir_l.x * dir_l.x + dir_l.y * dir_l.y + dir_l.z * dir_l.z);
		dir_l = vnorm(dir_l);
		e->tab_transp_l[0].t = -1;
		inter_obj(e, e->light[i].pos, dir_l);
		transp = 1;
		count = 0;
		color.x = e->light[i].color.x * 255;
		color.y = e->light[i].color.y * 255;
		color.z = e->light[i].color.z * 255;
		while (e->tab_transp_l[count].id != ct && transp != 0)
		{
			color.x = (color.x - e->tab_transp_l[count].color.x * transp) * (1 - e->tab_transp_l[count].ind_transp);
			color.y = (color.y - e->tab_transp_l[count].color.y * transp) * (1 - e->tab_transp_l[count].ind_transp);
			color.z = (color.z - e->tab_transp_l[count].color.z * transp) * (1 - e->tab_transp_l[count].ind_transp);
			transp -= (1 - e->tab_transp_l[count].ind_transp) * transp;
			count++;
		}
		dir_l = vmult_dbl(dir_l, -1);
		e->obj = e->tab_transp_l[count];
		if (e->obj.type == 1)
			ft_angle_sphere(e->obj, phit, dir_l, e->light[i], e);
		else if (e->obj.type == 2)
			ft_angle_plane(e->obj, dir_l, e->light[i], e);
		else if (e->obj.type == 3)
			ft_angle_cylinder(e->obj, phit, dir_l, e->light[i], e);
		else if (e->obj.type == 4)
			ft_angle_cone(e->obj, phit, dir_l, e->light[i], e);
		color.x >= 0 ? c.x += (e->c_hit.x - c.x) * color.x * e->angle / 255 * e->tab_transp_l[count].ind_transp : 0;
		color.y >= 0 ? c.y += (e->c_hit.y - c.y) * color.y * e->angle / 255 * e->tab_transp_l[count].ind_transp : 0;
		color.z >= 0 ? c.z += (e->c_hit.z - c.z) * color.z * e->angle / 255 * e->tab_transp_l[count].ind_transp : 0;
		c = l_color(c, color, e);
		i++;
	}
	e->flag = 0;
	return (c);
}

void		ft_raytracer3(__global t_env *e, double transp, double t)
{
	if (t == -1)
	{
		e->r = e->r * transp;
		e->g = e->g * transp;
		e->b = e->b * transp;
	}
}

void		ft_raytracer2(__global t_env *e, int count, double4 dir)
{
	int4 color;
	double4		phit;
	double		transp;

	transp = 0;
	while (e->tab_transp[count].t != -1 && transp != 1)
	{
		color.x = e->tab_transp[count].color.x * e->amb;
		color.y = e->tab_transp[count].color.y * e->amb;
		color.z = e->tab_transp[count].color.z * e->amb;
		phit = vhit(e->cam->eye, dir, e->tab_transp[count].t);
		e->c_hit = e->tab_transp[count].color;
		color = add_light(e, e->tab_transp[count].t, phit, e->tab_transp[count].id, color);
		e->r = (e->r * transp + color.x * e->tab_transp[count].ind_transp * (
			1 - transp)) / (transp + e->tab_transp[count].ind_transp * (1 - transp));
		e->g = (e->g * transp + color.y * e->tab_transp[count].ind_transp * (
			1 - transp)) / (transp + e->tab_transp[count].ind_transp * (1 - transp));
		e->b = (e->b * transp + color.z * e->tab_transp[count].ind_transp * (
			1 - transp)) / (transp + e->tab_transp[count].ind_transp * (1 - transp));
		transp += e->tab_transp[count].ind_transp * (1 - transp);
		count++;
		ft_raytracer3(e, transp, e->tab_transp[count].t);
	}
}

int4		ft_raytracer(int x, int y, __global t_env *e, int4 pixel)
{
	double4			ray;
	double4			dir;
	int				count;
	t_obj	tab_transp[e->nb_obj + 1];

	e->tab_transp = tab_transp;
	ray = new_v(e->cam->l.x + e->cam->u.x * x * (e->cam->w / (e->mlx->w * e->mlx->crenelage)) + e->
		cam->up.x * y * (e->cam->h / (e->mlx->h * e->mlx->crenelage)), e->cam->l.y + e->cam->u.y *
		x * (e->cam->w / (e->mlx->w * e->mlx->crenelage)) + e->cam->up.y * y * (e->cam->h / (e->mlx->h * e->mlx->crenelage))
		, e->cam->l.z + e->cam->u.z * x * (e->cam->w / (e->mlx->w * e->mlx->crenelage)) + e->
		cam->up.z * y * (e->cam->h / (e->mlx->h * e->mlx->crenelage)));
	dir = vsub(ray, e->cam->eye);
	dir = vnorm(dir);
	e->flag = 0;
	e->tab_transp[0].t = -1;
	e->r = 0;
	e->g = 0;
	e->b = 0;
	inter_obj(e, e->cam->eye, dir);
	if (e->tab_transp[0].t != -1)
	{
		count = 0;
		ft_raytracer2(e, count, dir);
		pixel = put_pixel(x, y, e);
	}
	return (pixel);
}
