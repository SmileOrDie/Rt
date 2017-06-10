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

void			ft_create_tab_obj_light(__global t_env_cl *e, int id, double tr, int *tab_obj_light_id, double *tab_obj_light_t)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (x < e->nb_obj && tab_obj_light_t[x] != -1 && tab_obj_light_t[x] <= tr)
		x++;
	while (y < e->nb_obj && tab_obj_light_t[y] != -1)
		y++;
	y++;
	while (y > x)
	{
		tab_obj_light_id[y] = tab_obj_light_id[y - 1];
		tab_obj_light_t[y] = tab_obj_light_t[y - 1];
		y--;
	}
	tab_obj_light_id[x] = id;
	tab_obj_light_t[x] = tr;
}

t_obj		inter_obj_light(__global t_env_cl *e, double4 p_ray, double4 v_ray, int *tab_obj_light_id, double *tab_obj_light_t)
{
	int			i;
	double		dist;

	i = 0;
	while (i < e->nb_obj)
	{
		if (e->l_obj[i].type == 1)
			dist = inter_sphere(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 2)
			dist = inter_plane(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 3)
			dist = inter_cylinder(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 4)
			dist = inter_cone(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 5)
			dist = inter_circle(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 6)
			dist = inter_square(e->l_obj[i], p_ray, v_ray);
		// else
 			// printf("nouvel obj = %d i = %d\n", e->l_obj[i].type, i);
		if (dist != -1)
			ft_create_tab_obj_light(e, i, dist, tab_obj_light_id, tab_obj_light_t);
		// else
		// {
			// printf("id = %d, px = %f et vf = %f\n", e->l_obj[i].id, p_ray.x, v_ray.x);
		// }
		i++;
	}
}

uchar4		l_shine(uchar4 c, uchar4 color, double angle)
{
	double 	power;
	int4	clamp;

	clamp.r = c.r;
	clamp.g = c.g;
	clamp.b = c.b;
	power = pow(ft_clamp(angle, 0, 1), 150);
	clamp.r += power * color.r;
	clamp.g += power * color.g;
	clamp.b += power * color.b;
	clamp.r > 255 ? (c.r = 255) : (c.r = clamp.r);
	clamp.g > 255 ? (c.g = 255) : (c.g = clamp.g);
	clamp.b > 255 ? (c.b = 255) : (c.b = clamp.b);
	return (c);
}

uchar4		add_light(__global t_env_cl *e, uchar4 pixel, double4 p_hit, t_obj obj)
{
	double4		v_light;
	double4		v_norm;
	int 		count;
	int 		i;
	double		calc;
	double		transp;
	uchar4		l_color;
	double		angles[e->nb_light + 1];
	int			tab_obj_light_id[e->nb_obj + 1];
	double		tab_obj_light_t[e->nb_obj + 1];

	i = 0;
	tab_obj_light_t[0] = -1;
	while (i < e->nb_light)
	{
		tab_obj_light_t[0] = -1;
		v_light = vsub(p_hit, e->light[i].pos);
		v_light = vnorm(v_light);
 		inter_obj_light(e, e->light[i].pos, v_light, tab_obj_light_id, tab_obj_light_t);
		l_color.r = e->light[i].color.r;
		l_color.g = e->light[i].color.g;
		l_color.b = e->light[i].color.b;
		transp = 1;
		count = 0;
		while (tab_obj_light_t[count] != -1 && tab_obj_light_id[count] != obj.id && transp != 0)
		{
			l_color.r *= (e->l_obj[tab_obj_light_id[count]].color.r / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			l_color.g *= (e->l_obj[tab_obj_light_id[count]].color.g / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			l_color.b *= (e->l_obj[tab_obj_light_id[count]].color.b / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			transp -= (1 - e->l_obj[tab_obj_light_id[count]].ind_transp) * transp;
			count++;
		}

		if (obj.type == 1)
			v_norm = ft_angle_sphere(obj, p_hit);
		else if (obj.type == 2 || obj.type == 5 || obj.type == 6)
			v_norm = ft_angle_plane(obj);
		else if (obj.type == 3)
			v_norm = ft_angle_cylinder(obj, p_hit);
		else if (obj.type == 4)
			v_norm = ft_angle_cone(obj, p_hit);
		angles[i] = vpscal(v_norm, vmult(v_light, -1));
		angles[i] < 0 ? (angles[i] *= -1) : 0;
		calc = angles[i] * transp / 255.0;
		pixel.r + obj.color.r * l_color.r * calc < 255 ? (pixel.r += obj.color.r * l_color.r * calc) : (pixel.r = 255);
		pixel.g + obj.color.g * l_color.g * calc < 255 ? (pixel.g += obj.color.g * l_color.g * calc) : (pixel.g = 255);
		pixel.b + obj.color.b * l_color.b * calc < 255 ? (pixel.b += obj.color.b * l_color.b * calc) : (pixel.b = 255);
		i++;
	}
	i = 0;
	while (i < e->nb_light)
	{
		pixel = l_shine(pixel, e->light[i].color, angles[i]);
		i++;
	}
	return (pixel);
}

__kernel void	ft_start_calc(__global uchar4 *color_lst, __global t_obj *lst_obj, __global t_light *light, __global t_env_cl *e, __global t_l_obj *lst)
{
	int index;
	uchar4 pixel;
	t_obj obj;

	index = get_global_id(0);
	// index == 0 ? printf(" t_env_cl_size %ld\n", sizeof(t_env_cl)) : 0;
	// index == 0 ? printf(" t_obj %ld\n", sizeof(t_obj)) : 0;
	// index == 0 ? printf(" t_l_obj %ld\n", sizeof(t_l_obj)) : 0;
	// index == 0 ? printf(" t_light %ld\n", sizeof(t_light)) : 0;
	e->light = light;
	e->l_obj = lst_obj;
	color_lst[index] = add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id]);
}
