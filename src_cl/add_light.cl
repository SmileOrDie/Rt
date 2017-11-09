/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/18 15:36:43 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			ft_create_tab_obj_light(__global t_env_cl *e, int id, double2 tr, int *tab_obj_light_id, double *tab_obj_light_t, int part2)
{
	int			x;
	int			y;

	// printf("je passe ici\n");
	x = 0;
	y = e->nb_obj * 2;
	while (x < e->nb_obj * 2 && tab_obj_light_t[x] <= tr[0])
		x++;
	while (y > x)
	{
		tab_obj_light_id[y] = tab_obj_light_id[y - 1];
		tab_obj_light_t[y] = tab_obj_light_t[y - 1];
		y--;
	}
	tab_obj_light_id[x] = id;
	tab_obj_light_t[x] = tr[0];
	if (part2)
	{
		x = 0;
		y = e->nb_obj * 2;
		while (x < e->nb_obj * 2 && tab_obj_light_t[x] <= tr[1])
			x++;
		while (y > x)
		{
			tab_obj_light_id[y] = tab_obj_light_id[y - 1];
			tab_obj_light_t[y] = tab_obj_light_t[y - 1];
			y--;
		}
		tab_obj_light_id[x] = id;
		tab_obj_light_t[x] = tr[1];
	}
	// printf("je repars la\n");
}

t_obj		inter_obj_light(__global t_env_cl *e, double4 p_ray, double4 v_ray, int *tab_obj_light_id, double *tab_obj_light_t)
{
	int			i;
	double2		dist;
	int 		toucher;

	i = 0;
	while (i < e->nb_obj)
	{
		toucher = 1;
		if (e->l_obj[i].type == 1)
			dist = inter_sphere(e->l_obj[i], p_ray, v_ray, &toucher);
		else if (e->l_obj[i].type == 2)
			dist = inter_plane(e->l_obj[i], p_ray, v_ray, &toucher);
		else if (e->l_obj[i].type == 3)
			dist = inter_cylinder(e->l_obj[i], p_ray, v_ray, &toucher);
		else if (e->l_obj[i].type == 4)
			dist = inter_cone(e->l_obj[i], p_ray, v_ray, &toucher);
		else if (e->l_obj[i].type == 5)
			dist = inter_circle(e->l_obj[i], p_ray, v_ray, &toucher);
		else if (e->l_obj[i].type == 6)
			dist = inter_square(e->l_obj[i], p_ray, v_ray, &toucher);
		// else
 			// printf("nouvel obj = %d i = %d\n", e->l_obj[i].type, i);
		if (toucher)
			ft_create_tab_obj_light(e, i, dist, tab_obj_light_id, tab_obj_light_t, (e->l_obj[i].type == 2 || e->l_obj[i].type == 5 || e->l_obj[i].type == 6) ? 0 : 1);
		// else
		// {
			// printf("id = %d, px = %f et vf = %f\n", e->l_obj[i].id, p_ray.x, v_ray.x);
		// }
		i++;
	}
}

uchar4		l_shine(uchar4 c, uchar4 color, double angle, double t)
{
	double 	power;
	int4	clamp;

	clamp.r = c.r;
	clamp.g = c.g;
	clamp.b = c.b;
	power = pow(ft_clamp(angle, 0, 1), 150) / t * 100;
	clamp.r += power * color.r;
	clamp.g += power * color.g;
	clamp.b += power * color.b;
	clamp.r > 255 ? (c.r = 255) : (c.r = clamp.r);
	clamp.g > 255 ? (c.g = 255) : (c.g = clamp.g);
	clamp.b > 255 ? (c.b = 255) : (c.b = clamp.b);
	return (c);
}

uchar4		get_color(__global t_mlx *texture, double4 p_hit, t_obj obj)
{
	double4	dir;
	uchar4	color;
	double4 test;
	double4	tmp;
	double	x;
	double 	y;
	int		pix;

	if (obj.type == 1 && obj.id_texture > 0)
	{
		dir = vsub(p_hit, obj.pos);
		dir = vnorm(dir);
		x = 0.5 + atan2(dir.z, dir.x) / (2 * M_PI);
		y = 0.5 - asin(dir.y) / M_PI;
		x = x * texture[obj.id_texture - 1].w;
		y = y * texture[obj.id_texture - 1].h;
		pix = (int)y * 4 * texture[obj.id_texture - 1].w + (int)x * 4;
		color.b = ((uchar *)(texture[obj.id_texture -1].data))[pix + 0];
		color.g = ((uchar *)(texture[obj.id_texture -1].data))[pix + 1];
		color.r = ((uchar *)(texture[obj.id_texture -1].data))[pix + 2];
		return (color);
	}
	else if ((obj.type == 2 || obj.type == 5 || obj.type == 6) && obj.id_texture > 0)
	{
		dir = vsub(p_hit, obj.pos);
		test = (obj.dir.x == 1 || obj.dir.x == -1) ? (double4){0, 1, 0, 0} : (double4){1, 0, 0, 0};
		tmp = vcross(obj.dir, test);
		tmp = vnorm(tmp);
		x = ((int)vpscal(tmp, dir)) % texture[obj.id_texture - 1].w;
		x < 0 ? x += texture[obj.id_texture - 1].w : 0;
		tmp = vcross(tmp, obj.dir);
		y = ((int)vpscal(tmp, dir)) % texture[obj.id_texture - 1].h;
		y < 0 ? y += texture[obj.id_texture - 1].h : 0;

		pix = (int)y * 4 * texture[obj.id_texture - 1].w + (int)x * 4;
		color.b = ((uchar *)(texture[obj.id_texture - 1].data))[pix + 0];
		color.g = ((uchar *)(texture[obj.id_texture - 1].data))[pix + 1];
		color.r = ((uchar *)(texture[obj.id_texture - 1].data))[pix + 2];
		return (color);
	}
	else if (obj.type == 4 && obj.id_texture > 0)
	{
		dir = vsub(p_hit, obj.pos);
		tmp = vmult_dbl(obj.dir, vpscal(dir, obj.dir));
		tmp = vsub(p_hit, tmp);
		tmp = vrot(vcross(obj.dir, (double4){0, 0, 1, 0}), acos(vpscal(obj.dir, (double4){0, 0, 1, 0})), tmp);
		x = 0.5 + atan2(tmp.y, tmp.x) / (2 * M_PI);
		y = (int)(vsize(dir)) % texture[obj.id_texture - 1].h;
		y < 0 ? y += texture[obj.id_texture - 1].h : 0;
		x = x * texture[obj.id_texture - 1].w;
		pix = (int)y * 4 * texture[obj.id_texture - 1].w + (int)x * 4;
		color.b = ((uchar *)(texture[obj.id_texture -1].data))[pix + 0];
		color.g = ((uchar *)(texture[obj.id_texture -1].data))[pix + 1];
		color.r = ((uchar *)(texture[obj.id_texture -1].data))[pix + 2];
		return (color);
	}
	else if (obj.type == 3 && obj.id_texture > 0)
	{
		dir = vsub(p_hit, obj.pos);
		tmp = vmult_dbl(obj.dir, vpscal(dir, obj.dir));
		tmp = vsub(p_hit, tmp);
		tmp = vrot(vcross(obj.dir, (double4){0, 0, 1, 0}), acos(vpscal(obj.dir, (double4){0, 0, 1, 0})), tmp);
		x = 0.5 + atan2(tmp.y, tmp.x) / (2 * M_PI);
		y = (int)(vpscal(dir, obj.dir)) % texture[obj.id_texture - 1].h;
		y < 0 ? y += texture[obj.id_texture - 1].h : 0;
		x = x * texture[obj.id_texture - 1].w;
		pix = (int)y * 4 * texture[obj.id_texture - 1].w + (int)x * 4;
		color.b = ((uchar *)(texture[obj.id_texture -1].data))[pix + 0];
		color.g = ((uchar *)(texture[obj.id_texture -1].data))[pix + 1];
		color.r = ((uchar *)(texture[obj.id_texture -1].data))[pix + 2];
		return (color);
	}
	return (obj.color);
}


uchar4		add_light(__global t_env_cl *e, uchar4 pixel, double4 p_hit, t_obj obj, __global t_mlx *texture, int index)
{
	double4		v_light;
	double4		v_norm;
	int 		count;
	int 		i;
	double		calc;
	uchar4		l_color;
	uchar4		colorobj;
	double		angles[e->nb_light + 1];
	double		dist[e->nb_light + 1];
	int			tab_obj_light_id[e->nb_obj * 2 + 1];
	double		tab_obj_light_t[e->nb_obj * 2 + 1];
	char		list_obj[e->nb_obj];
	char		list_group[e->group_max];
	int			flag;
	int			t;
	uchar4		tmp_color;

	i = 0;
	colorobj = get_color(texture, p_hit, obj);
	while (i < e->nb_light)
	{
		tab_obj_light_id[0] = -1;
		v_light = vsub(p_hit, e->light[i].pos);
		v_light = vnorm(v_light);
	// printf("d inter_obj_light\n");
		tab_obj_light_t[0] = 99999999999999999999l;
 		inter_obj_light(e, e->light[i].pos, v_light, tab_obj_light_id, tab_obj_light_t);
	// printf("f inter_obj_light\n");
		l_color.r = e->light[i].color.r;
		l_color.g = e->light[i].color.g;
		l_color.b = e->light[i].color.b;
		count = 0;
		flag = 0;
		t = 0;
		while (t < e->nb_obj)
		{
			list_obj[t] = 0;
			t < e->group_max ? list_group[t] = 0 : 0;
			t++;
		}
		t = 0;
		while (tab_obj_light_id[t] != -1)
		{
			if (e->l_obj[tab_obj_light_id[t]].group == 0)
				list_obj[tab_obj_light_id[t]] = (list_obj[tab_obj_light_id[t]] || e->l_obj[tab_obj_light_id[t]].type == 5 || e->l_obj[tab_obj_light_id[t]].type == 2 || e->l_obj[tab_obj_light_id[t]].type == 6) ? 0 : 1;
			else
				list_group[e->l_obj[tab_obj_light_id[t]].group] = list_group[e->l_obj[tab_obj_light_id[t]].group] ? 0 : 1;
			t++;
		}
		while (tab_obj_light_t[count] < vsize(vsub(p_hit, e->light[i].pos)) - 1)
		{
			if (e->l_obj[tab_obj_light_id[count]].group == 0)
				list_obj[tab_obj_light_id[count]] = (list_obj[tab_obj_light_id[count]] || e->l_obj[tab_obj_light_id[count]].type == 5 || e->l_obj[tab_obj_light_id[count]].type == 2 || e->l_obj[tab_obj_light_id[count]].type == 6) ? 0 : 1;
			else
				list_group[e->l_obj[tab_obj_light_id[count]].group] = list_group[e->l_obj[tab_obj_light_id[count]].group] ? 0 : 1;
			flag = 0;
			t = 0;
			while (t < e->nb_obj)
			{
				if (e->l_obj[t].negatif)
				{
					if (e->l_obj[t].group != 0)
					{
						if (list_group[e->l_obj[t].group])
							flag = 1;
					}
					else
					{
						if (list_obj[t])
							flag = 1;
					}
				}
				t++;
			}
			if (tab_obj_light_t[count] >= 0 && flag == 0)
			{
				tmp_color = get_color(texture, vadd(e->light[i].pos, vmult_dbl(v_light, tab_obj_light_t[count])), e->l_obj[tab_obj_light_id[count]]);
				// tmp_color = e->l_obj[tab_obj_light_id[count]].color;
				tmp_color.r *= 1 - e->l_obj[tab_obj_light_id[count]].ind_reflec;
				tmp_color.b *= 1 - e->l_obj[tab_obj_light_id[count]].ind_reflec;
				tmp_color.g *= 1 - e->l_obj[tab_obj_light_id[count]].ind_reflec;
				l_color.r = l_color.r * (double)((tmp_color.r / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp));
				l_color.g = l_color.g * (double)((tmp_color.g / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp));
				l_color.b = l_color.b * (double)((tmp_color.b / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp));
			}
			// else if (tab_obj_light_t[count] >= 0 && list_obj[tab_obj_light_id[count]] && flag == 1 && e->l_obj[tab_obj_light_id[count]].negatif == 0 && e->l_obj[tab_obj_light_id[count]].type == 2)
			//	printf("type = %d et name = %s\n", e->l_obj[tab_obj_light_id[count]].type, e->l_obj[tab_obj_light_id[count]].name);
			count++;
		}
		// printf("Bienvenue ==================\n");
		// t = 0;
		// while (t < e->nb_obj)
		// {
		// 	list_obj[t] ? printf("%d", e->l_obj[t].type) : 0;
		// 	t++;
		// }
		if (obj.type == 1)
			v_norm = ft_angle_sphere(obj, p_hit);
		else if (obj.type == 2 || obj.type == 5 || obj.type == 6)
			v_norm = ft_angle_plane(obj);
		else if (obj.type == 3)
			v_norm = ft_angle_cylinder(obj, p_hit);
		else if (obj.type == 4)
			v_norm = ft_angle_cone(obj, p_hit);
		angles[i] = vpscal(v_norm, vmult(v_light, -1));
		if (angles[i] < 0)
			angles[i] *= -1;
		calc = angles[i] / 255.0;
		pixel.r + colorobj.r * l_color.r * calc < 255 ? (pixel.r += colorobj.r * l_color.r * calc) : (pixel.r = 255);
		pixel.g + colorobj.g * l_color.g * calc < 255 ? (pixel.g += colorobj.g * l_color.g * calc) : (pixel.g = 255);
		pixel.b + colorobj.b * l_color.b * calc < 255 ? (pixel.b += colorobj.b * l_color.b * calc) : (pixel.b = 255);
		dist[i] = tab_obj_light_t[count];
		// 	if (tab_obj_light_t[count] == 0)
		// printf("il y a un problem ?\n");
		i++;
	}
	pixel.r = pixel.r * (1 - (double)(e->amb) / 100.0) + colorobj.r * e->amb / 100.0;
	pixel.g = pixel.g * (1 - (double)(e->amb) / 100.0) + colorobj.g * e->amb / 100.0;
	pixel.b = pixel.b * (1 - (double)(e->amb) / 100.0) + colorobj.b * e->amb / 100.0;
	i = 0;
	while (i < e->nb_light)
	{
		pixel = l_shine(pixel, e->light[i].color, angles[i], dist[i]);
		i++;
	}
	return (pixel);
}

__kernel void	ft_start_calc(__global uchar4 *color_lst, __global t_obj *lst_obj, __global t_light *light, __global t_env_cl *e, __global t_l_obj *lst, __global t_mlx *texture)
{
	int		index;
	uchar4	pixel;
	t_obj	obj;
	int y;

	index = get_global_id(0);
	// if (index == 0)
	// {
	// 	y = 0;
	// 	printf("size = %d %d\n", texture[2].w, texture[2].h);
	// 	while (y < texture[2].w * texture[2].h)
	// 	{
	// 		printf("%d ", ((char *)(texture[2].data))[y]);
	// 		y++;
	// 	}
	// }
	// index == 0 ? printf(" t_obj %ld\n", sizeof(t_obj)) : 0;
	// index == 0 ? printf(" t_l_obj %ld\n", sizeof(t_l_obj)) : 0;
	// index == 0 ? printf(" t_light %ld\n", sizeof(t_light)) : 0;
	e->light = light;
	e->l_obj = lst_obj;
	color_lst[index] = add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id], texture, index);
}
