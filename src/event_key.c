/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/05 15:42:11 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int		keypress(int key, t_envg *e)
{
	pthread_join(e->thread, NULL);
	if (key == ESC)
	{
		// ft_exit3(e->e);
		ft_exit(e);
		e->e->b_screen = 1;
	}
	if (key == 123)
	{
		e->e->cam->eye.x += 10;
		e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
		vnorm(&e->e->cam->n);
		e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
		e->e->cam->n.x);
		e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
		e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
		e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
		e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
		(e->e->cam->h / 2));
	}
	else if (key == 124)
	{
		e->e->cam->eye.x -= 10;
		e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
		vnorm(&e->e->cam->n);
		e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
		e->e->cam->n.x);
		e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
		e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
		e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
		e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
		(e->e->cam->h / 2));
	}
	else if (key == 125)
	{
		e->e->cam->eye.y += 10;
		e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
		vnorm(&e->e->cam->n);
		e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
		e->e->cam->n.x);
		e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
		e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
		e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
		e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
		(e->e->cam->h / 2));
		// pthread_create(&thread, NULL, ft_launch, e->e);
		// e->e->cam->l_at.y += 10;
	}
	else if (key == 126)
	{
		e->e->cam->eye.y -= 10;
		e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
		vnorm(&e->e->cam->n);
		e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
		e->e->cam->n.x);
		e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
		e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
		e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
		e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
		(e->e->cam->h / 2));
		// e->e->cam->l_at.y -= 10;
			// pthread_create(&e->thread, NULL, ft_launch, e->e);
			// pthread_join(e->thread, NULL);
	}
	else
		return (1);
	pthread_create(&e->thread, NULL, ft_launch, e->e);
	return (1);
}

int		redcross(t_env *e)
{
	(void)e;
	exit(1);
	return (1);
}
