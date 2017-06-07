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
	// id != 1 ? printf("id = %d tr = %f\n", id, tr) : 0;
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
 		// printf("des baiser\n");
		// printf("test\n");
		// printf("e->l_obj[i].id = %d\n", e->l_obj[i].id);
		if (e->l_obj[i].type == 1)
			dist = inter_sphere(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 2)
			dist = inter_plane(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 3)
			dist = inter_cylinder(e->l_obj[i], p_ray, v_ray);
		else if (e->l_obj[i].type == 4)
			dist = inter_cone(e->l_obj[i], p_ray, v_ray);
		else
 			printf("nouvelle obj = %d i = %d\n", e->l_obj[i].type, i);
		if (dist != -1)
			ft_create_tab_obj_light(e, i, dist, tab_obj_light_id, tab_obj_light_t);
		else
		{
			// printf("id = %d, px = %f et vf = %f\n", e->l_obj[i].id, p_ray.x, v_ray.x);
		}
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

	// write(1, "coucou\n", 7);
	// write(1, atoi(e->nb_obj), strlen(atoi(e->nb_obj)));
	// printf("p_hit %f %f %f\n", p_hit.x, p_hit.y, p_hit.z);
	while (i < e->nb_light)
	{	
		tab_obj_light_t[0] = -1;

		// printf("light.pos %f %f %f\n", e->light[i].pos.x, e->light[i].pos.y, e->light[i].pos.z);
		v_light = vsub(p_hit, e->light[i].pos);
		// printf("------------------------------------------ \n");
		v_light = vnorm(v_light);
		// printf("------------------------------------------ \n");
		// printf("b tab_obj_light_id[0] = %d et tab_obj_light_id[1] = %d\n", tab_obj_light_id[0], tab_obj_light_id[1]);
		// printf("b tab_obj_light_t[0] = %f et tab_obj_light_t[1] = %f\n", tab_obj_light_t[0], tab_obj_light_t[1]);
 		inter_obj_light(e, e->light[i].pos, v_light, tab_obj_light_id, tab_obj_light_t);
		// printf("a tab_obj_light_id[0] = %d et tab_obj_light_id[1] = %d\n", tab_obj_light_id[0], tab_obj_light_id[1]);
		// printf("a tab_obj_light_t[0] = %f et tab_obj_light_t[1] = %f\n\n", tab_obj_light_t[0], tab_obj_light_t[1]);
 		// printf("------------------------------------------ %d > %d\n", e->nb_light, i);
		l_color.r = e->light[i].color.r;
		l_color.g = e->light[i].color.g;
		l_color.b = e->light[i].color.b;
		// printf("color : %d %d %d\n", l_color.r, l_color.g, l_color.b);
		transp = 1;
		count = 0;
		// printf("obj.color : %d %d %d\n", obj.color.r, obj.color.g, obj.color.b);
		// printf("l_color : %d %d %d\n", l_color.r, l_color.g, l_color.b);
		// printf("color : %d %d %d\n", obj.color.r, obj.color.g, obj.color.b);
		while (tab_obj_light_t[count] != -1 && tab_obj_light_id[count] != obj.id && transp != 0)
		{
			l_color.r *= (e->l_obj[tab_obj_light_id[count]].color.r / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			l_color.g *= (e->l_obj[tab_obj_light_id[count]].color.g / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			l_color.b *= (e->l_obj[tab_obj_light_id[count]].color.b / 255.0) * (e->l_obj[tab_obj_light_id[count]].ind_transp);
			transp -= (1 - e->l_obj[tab_obj_light_id[count]].ind_transp) * transp;
			// printf("tab_obj_light_id[%d] = %d, e->l_obj[tab_obj_light_id[count]].color.r = %d\n", count, tab_obj_light_id[count], e->l_obj[tab_obj_light_id[count]].color.r);
			count++;
		}

		if (obj.type == 1)
			v_norm = ft_angle_sphere(obj, p_hit);
		else if (obj.type == 2)
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
		// printf("color : %d %d %d\n", pixel.r, pixel.g, pixel.b);
		i++;
	}
	i = 0;
	while (i < e->nb_light)
	{
		pixel = l_shine(pixel, e->light[i].color, angles[i]);
		i++;
	}
	// if ((pixel.r + pixel.g + pixel.b) / 3 - pixel.b > -1)
	// 	printf("i'm blue\n");
	return (pixel);
}

// uchar4	ft_start( __global t_env_cl *e, __global t_obj *lst_obj, t_l_obj lst)
// {
// 	return (add_light(e, lst_obj[lst.id]), lst.color_light, lst.p_hit);
// }


__kernel void	ft_start_calc(__global uchar4 *color_lst, __global t_obj *lst_obj, __global t_light *light, __global t_env_cl *e, __global t_l_obj *lst)
{
	int index;
	uchar4 pixel;
	// int i;

	index = get_global_id(0);

	t_obj obj;

	// printf("%d %d %d\n", e->light[1].color.r , e->light[1].color.g , e->light[1].color.b);
	// printf("kernel =%d :> nb_light = %d, nb_obj = %d\n", index, e->nb_light ,e->nb_obj);
	// e->l_obj = lst_obj;
	// printf("%d",index);

	if (index == 0)
	{
	// printf("p = %f %f %f, cb = %d\n", lst_obj[0].pos.x, lst_obj[0].pos.y, lst_obj[0].pos.z, lst_obj[0].color.b);
	// printf("p = %f %f %f, cb = %d\n", lst_obj[1].pos.x, lst_obj[1].pos.y, lst_obj[1].pos.z, lst_obj[1].color.b);
	// printf("p = %f %f %f, cb = %d\n", lst_obj[2].pos.x, lst_obj[2].pos.y, lst_obj[2].pos.z, lst_obj[2].color.b);
	// printf("p = %f %f %f, cb = %d\n", lst_obj[3].pos.x, lst_obj[3].pos.y, lst_obj[3].pos.z, lst_obj[3].color.b);
			// printf(" t_env_cl_size %lu\n", sizeof(t_env_cl));
			// printf(" t_obj %lu\n", sizeof(t_obj));
			// printf(" t_l_obj %lu\n", sizeof(t_l_obj));
			// printf(" t_light %lu\n", sizeof(t_light));
			// printf(" double4 %lu\n", sizeof(double4));
			// printf(" uchar4 %lu\n", sizeof(uchar4));
			// printf(" void* %lu\n", sizeof(void *));
			// printf("Total = %lu\n", sizeof(int) * 2 + sizeof(void*) + sizeof(double4) * 3 + sizeof(double) * 5 + sizeof(uchar4));
			// printf(" lst %li\n", (long)&(e->color_lst) - (long)&(e->lst));
			// printf(" color_lst %li\n", (long)&(e->light) - (long)&(e->color_lst));
			// printf(" light %li\n", (long)&(e->l_obj) - (long)&(e->light));
			// printf(" l_obj %li\n", (long)&(e->nb_obj) - (long)&(e->l_obj));
			// printf(" nb_obj %li\n", (long)&(e->nb_light) - (long)&(e->nb_obj));
			// printf(" nb_light %li\n", (long)&(e->cl) - (long)&(e->nb_light));
			// printf(" cl %li\n", (long)&(e->vacuum) - (long)&(e->cl));
			// printf(" vacuum %li\n", (long)&(e->vacuum2) - (long)&(e->vacuum));
			// printf(" vacumm2 %li\n", (long)&(e->vacuum) - (long)&(e->vacuum2));
			// printf(" type %li\n", (long)&(obj.id) - (long)&(obj.type));
			// printf(" id %li\n", (long)&(obj.radius) - (long)&(obj.id));
			// printf(" radius %li\n", (long)&(obj.ind_refrac) - (long)&(obj.radius));
			// printf(" pos %li\n", (long)&(obj.dir) - (long)&(obj.pos));
			// printf(" dir %li\n", (long)&(obj.point) - (long)&(obj.dir));
			// printf(" point %li\n", (long)&(obj.color) - (long)&(obj.point));
			// printf(" color %li\n", (long)&(obj.angle) - (long)&(obj.color));
			// printf(" angle %li\n", (long)&(obj.name) - (long)&(obj.angle));
			// printf(" name %li\n", (long)&(obj.ind_transp) - (long)&(obj.name));
	}
	e->light = light;
	e->l_obj = lst_obj;

	// printf("id de depart = %d\n", lst[index].id);
	// e->vacuum;

	// printf("index %d\n", index);
	// printf("lst[index].p_hit_x = %f\n", lst[index].p_hit_x);
	// printf("lst[index].p_hit_y = %f\n", lst[index].p_hit_y);
	// printf("lst[index].p_hit_z = %f\n", lst[index].p_hit_z);
	// printf("lst_obj[0].pos.x = %d\n", lst_obj[0].pos.x);
	// printf("vacuum = %ld\n", e->vacuum);
	// i = index
	// while (index % 2 != 1)
	// printf("Ah que coucou bob\n");
	// {
	// pixel = add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id]);
	// color_lst[index] = (uchar4){(unsigned char)pixel.r, (unsigned char)pixel.g, (unsigned char)pixel.b, 0};
	color_lst[index] = add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id]);
	// if (color_lst[index] == (uchar4){0, 0, 255, 0})
	// 	printf("I'm blue\n");
		// index++;
	// }
	// if (e->vacuum > index)
	// {
		// pixel = add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id]);
		// color_lst[index] = (uchar4){(unsigned char)pixel.x, (unsigned char)pixel.y, (unsigned char)pixel.z, 0};
	// }// add_light(e, (uchar4){0, 0, 0, 0}, (double4){lst[index].p_hit_x, lst[index].p_hit_y, lst[index].p_hit_z, 0}, lst_obj[lst[index].id]);
	// printf("kernel =%d :> color_lst =  %d %d %d obj.id = %d\n", index,color_lst[index].r ,color_lst[index].g, color_lst[index].b, lst_obj[lst[index].id].id);
}






































