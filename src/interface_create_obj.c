/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/11/09 13:20:53 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_cam	g_default_camera_g = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, 60, 150,
	480, 650, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, 1, 0};

static void			creat_light(t_envg *e)
{
	t_parse_light *b;
	t_parse_light *new;

	if (!(new = (t_parse_light *)malloc(sizeof(t_parse_light))))
		ft_error(MALLOC, "new_l -> inteface_create_obj.h");
	new->light = new_light(e);
	new->next = NULL;
	b = e->parse_light;
	if (b)
	{
		while (b->next)
			b = b->next;
		b->next = new;
	}
	else
		e->parse_light = new;
}

static void			creat_obj(t_envg *e)
{
	t_parse_obj *b;
	t_parse_obj *new;

	if (!(new = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		ft_error(MALLOC, "new -> inteface_create_obj.h");
	new->obj = new_obj(e);
	new->next = NULL;
	b = e->parse_obj;
	if (b)
	{
		while (b->next)
			b = b->next;
		b->next = new;
	}
	else
		e->parse_obj = new;
}

void				creat_elem(t_envg *e)
{
	if ((e->error = check_var_obj(e->line)) != -1)
		return ;
	if (!ft_strcmp("light", e->line[1]))
		creat_light(e);
	else
		creat_obj(e);
	reset_line(e->line);
}

t_vector			creat_cam_2(t_envg *e, int i)
{
	if (i == 1)
		return (new_v(e->cam.up.y * e->cam.n.z - e->cam.up.z *
		e->cam.n.y, e->cam.up.z * e->cam.n.x - e->cam.up.x *
		e->cam.n.z, e->cam.up.x * e->cam.n.y - e->cam.up.y *
		e->cam.n.x));
	else if (i == 0)
		return (new_v(e->cam.c.x - e->cam.u.x * (e->cam.w / 2) -
		e->cam.up.x * (e->cam.h / 2), e->cam.c.y - e->cam.u.y *
		(e->cam.w / 2) - e->cam.up.y * (e->cam.h / 2),
		e->cam.c.z - e->cam.u.z * (e->cam.w / 2) -
		e->cam.up.z * (e->cam.h / 2)));
		return (new_v(0, 0, 0));
}

void				creat_cam(t_envg *e)
{
	e->win.w = ft_atoi(e->line[25]) * e->anti_a;
	e->win.h = ft_atoi(e->line[26]) * e->anti_a;
	e->cam = g_default_camera_g;
	e->cam.eye = new_v(ft_atof(e->line[19]), ft_atof(e->line[20]),
		ft_atof(e->line[21]));
	e->cam.l_at = new_v(ft_atof(e->line[22]), ft_atof(e->line[23]),
		ft_atof(e->line[24]));
	e->cam.up = new_v(0.0, -1.0, 0.0);
	vnorm(&e->cam.up);
	e->cam.fov = 60.0;
	e->cam.dist = 150.0;
	e->cam.n = vsub(e->cam.eye, e->cam.l_at);
	vnorm(&e->cam.n);
	e->cam.u = creat_cam_2(e, 1);
	e->cam.h = tan(M_PI * (e->cam.fov / 2) / 180) * 2 * e->cam.dist;
	e->cam.w = e->cam.h * ((float)e->win.w / e->win.h);
	e->cam.c = new_v(e->cam.eye.x - e->cam.n.x * e->cam.dist,
		e->cam.eye.y - e->cam.n.y * e->cam.dist,
		e->cam.eye.z - e->cam.n.z * e->cam.dist);
	e->cam.l = creat_cam_2(e, 0);
}
