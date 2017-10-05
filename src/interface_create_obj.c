/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/10/05 16:49:59 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_cam	g_default_camera_g = {{0, 0, -300, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, 60,
{0, 0, 1, 0}, 0};

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

void				creat_cam(t_envg *e)
{
	e->win.w = ft_atoi(e->line[25]) * e->anti_a;
	e->win.h = ft_atoi(e->line[26]) * e->anti_a;
	e->cam = g_default_camera_g;
	e->cam.eye = new_v(ft_atof(e->line[19]), ft_atof(e->line[20]),
		ft_atof(e->line[21]));
	e->cam.l_at = new_v(ft_atof(e->line[22]), ft_atof(e->line[23]),
		ft_atof(e->line[24]));
	e->cam.dir = vsub(e->cam.l_at, e->cam.eye);
	if (e->cam.dir.x == 0 && e->cam.dir.y == 0 && e->cam.dir.z == 0)
		e->cam.dir.z = 1;
	vnorm(&e->cam.dir);
	e->cam.up = new_v(0.0, 1.0, 0.0);
	e->cam.up = vcross(e->cam.dir, vcross(e->cam.up, e->cam.dir));
	e->cam.set = 1;
}
