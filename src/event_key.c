/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/04 13:52:19 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		cam_cal(t_envg *e, t_vector l, int l_at)
{
	if (l_at == 0)
		e->e->cam.eye = vadd(e->e->cam.eye, l);
	else
		e->e->cam.l_at = vadd(e->e->cam.l_at, l);
	e->e->cam.n = vsub(e->e->cam.eye, e->e->cam.l_at);
	vnorm(&e->e->cam.n);
	e->e->cam.u = new_v(e->e->cam.up.y * e->e->cam.n.z - e->e->cam.up.z *
	e->e->cam.n.y, e->e->cam.up.z * e->e->cam.n.x - e->e->cam.up.x *
	e->e->cam.n.z, e->e->cam.up.x * e->e->cam.n.y - e->e->cam.up.y *
	e->e->cam.n.x);
	e->e->cam.h = tan(M_PI * (e->e->cam.fov / 2) / 180) * 2 * e->e->cam.dist;
	e->e->cam.w = e->e->cam.h * ((float)e->e->win.w / e->e->win.h);
	e->e->cam.c = new_v(e->e->cam.eye.x - e->e->cam.n.x * e->e->cam.dist,
	e->e->cam.eye.y - e->e->cam.n.y * e->e->cam.dist,
	e->e->cam.eye.z - e->e->cam.n.z * e->e->cam.dist);
	e->e->cam.l = new_v(e->e->cam.c.x - e->e->cam.u.x * (e->e->cam.w / 2) -
	e->e->cam.up.x * (e->e->cam.h / 2), e->e->cam.c.y - e->e->cam.u.y *
	(e->e->cam.w / 2) - e->e->cam.up.y * (e->e->cam.h / 2),
	e->e->cam.c.z - e->e->cam.u.z * (e->e->cam.w / 2) - e->e->cam.up.z *
	(e->e->cam.h / 2));
}

static int		keypress_2(int key, t_envg *e, int nb_press)
{
	if (key == KEY_W)
		cam_cal(e, (t_vector){0, 10 * nb_press, 0, 0}, 1);
	else if (key == RIGHT)
		cam_cal(e, (t_vector){-10 * nb_press, 0, 0, 0}, 0);
	else if (key == DOWN)
		cam_cal(e, (t_vector){0, 10 * nb_press, 0, 0}, 0);
	else if (key == UP)
		cam_cal(e, (t_vector){0, -10 * nb_press, 0, 0}, 0);
	else if (key == PAD_TIRET)
		cam_cal(e, (t_vector){0, 0, -10 * nb_press, 0}, 0);
	else if (key == PAD_PLUS)
		cam_cal(e, (t_vector){0, 0, 10 * nb_press, 0}, 0);
	else if (key == KEY_S)
		cam_cal(e, (t_vector){0, -10 * nb_press, 0, 0}, 1);
	else if (key == KEY_A)
		cam_cal(e, (t_vector){10 * nb_press, 0, 0, 0}, 1);
	else if (key == KEY_D)
		cam_cal(e, (t_vector){-10 * nb_press, 0, 0, 0}, 1);
	else if (key == KEY_R)
		cam_cal(e, (t_vector){0, 0, 10 * nb_press, 0}, 1);
	else if (key == KEY_F)
		cam_cal(e, (t_vector){0, 0, -10 * nb_press, 0}, 1);
	else
		return (0);
	return (1);
}

int				keypress(int key, t_envg *e)
{
	static int nb_press = 1;

	if (e->e->flag == 1)
	{
		nb_press++;
		return (1);
	}
	else
	{
		e->e->wait = 0;
		if (key == ESC)
		{
			ft_exit(e);
			e->e->b_screen = 1;
		}
		if (key == LEFT)
			cam_cal(e, (t_vector){10 * nb_press, 0, 0, 0}, 0);
		else if (!keypress_2(key, e, nb_press))
			return (1);
		pthread_create(&e->thread, NULL, ft_launch, e->e);
		e->e->flag = 1;
		nb_press = 1;
	}
	return (1);
}
