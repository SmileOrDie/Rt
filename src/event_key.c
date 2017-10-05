/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/10/05 17:00:20 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int		keypress_2(int key, t_envg *e, int nb_press)
{
	t_vector	cross;
	double		len;

	(void)nb_press;
	cross = vcross(e->e->cam.up, e->e->cam.dir);
	vnorm(&cross);
	if (key == KEY_W)
	{
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(e->e->cam.up, 10 * nb_press));
		e->e->cam.l_at = vadd(e->e->cam.l_at, vmult_dbl(e->e->cam.up, 10 * nb_press));
	}
	else if (key == KEY_S)
	{
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(e->e->cam.up, -10 * nb_press));
		e->e->cam.l_at = vadd(e->e->cam.l_at, vmult_dbl(e->e->cam.up, -10 * nb_press));
	}
	else if (key == KEY_A)
	{
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(cross, -10 * nb_press));
		e->e->cam.l_at = vadd(e->e->cam.l_at, vmult_dbl(cross, -10 * nb_press));
	}
	else if (key == KEY_D)
	{
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(cross, 10 * nb_press));
		e->e->cam.l_at = vadd(e->e->cam.l_at, vmult_dbl(cross, 10 * nb_press));
	}
	else if (key == RIGHT)
	{
		e->e->cam.dir = vmult_dbl(vrot(e->e->cam.up, -1 * nb_press, e->e->cam.dir), -1);
		len = vsize(vsub(e->e->cam.l_at, e->e->cam.eye));
		e->e->cam.eye = vmult_dbl(e->e->cam.dir, len);
	}
	else if (key == LEFT)
	{
		e->e->cam.dir = vmult_dbl(vrot(e->e->cam.up, 1 * nb_press, e->e->cam.dir), -1);
		len = vsize(vsub(e->e->cam.l_at, e->e->cam.eye));
		e->e->cam.eye = vmult_dbl(e->e->cam.dir, len);
	}
	else if (key == DOWN)
	{
		e->e->cam.dir = vmult_dbl(vrot(cross, -1 * nb_press, e->e->cam.dir), -1);
		len = vsize(vsub(e->e->cam.l_at, e->e->cam.eye));
		e->e->cam.eye = vmult_dbl(e->e->cam.dir, len);
	}
	else if (key == UP)
	{
		e->e->cam.dir = vmult_dbl(vrot(cross, 1 * nb_press, e->e->cam.dir), -1);
		len = vsize(vsub(e->e->cam.l_at, e->e->cam.eye));
		e->e->cam.eye = vmult_dbl(e->e->cam.dir, len);
	}
	else if (key == PAD_TIRET)
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(e->e->cam.dir, -10 * nb_press));
	else if (key == PAD_PLUS)
		e->e->cam.eye = vadd(e->e->cam.eye, vmult_dbl(e->e->cam.dir, 10 * nb_press));
	else
		return (0);
	e->e->cam.dir = vsub(e->e->cam.l_at, e->e->cam.eye);
	vnorm(&e->e->cam.dir);
	e->e->cam.up = vcross(vcross(e->e->cam.dir, e->e->cam.up), e->e->cam.dir);
	vnorm(&e->e->cam.up);
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
		printf("nb_press = %d\n", nb_press);
		e->e->wait = 0;
		if (key == ESC)
		{
			ft_exit(e);
			e->e->b_screen = 1;
		}
		else if (!keypress_2(key, e, nb_press))
			return (1);
		pthread_create(&e->thread, NULL, ft_launch, e->e);
		e->e->flag = 1;
		nb_press = 1;
	}
	return (1);
}
