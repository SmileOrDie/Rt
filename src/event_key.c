/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 19:50:34 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		keypress2(t_envg *e)
{
	e->e->cam->eye.x += 10;
	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	vnorm(&e->e->cam->n);
	e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z
	* e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x
	* e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y
	* e->e->cam->n.x);
	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2
	* e->e->cam->dist;
	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x *
	e->e->cam->dist, e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
	e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x *
	(e->e->cam->w / 2) - e->e->cam->up.x * (e->e->cam->h / 2),
	e->e->cam->c.y - e->e->cam->u.y * (e->e->cam->w / 2) - e->e->cam->up.y
	* (e->e->cam->h / 2), e->e->cam->c.z - e->e->cam->u.z *
	(e->e->cam->w / 2) - e->e->cam->up.z *
	(e->e->cam->h / 2));
}

void		keypress3(t_envg *e)
{
	e->e->cam->eye.x -= 10;
	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	vnorm(&e->e->cam->n);
	e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z -
	e->e->cam->up.z * e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x -
	e->e->cam->up.x * e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y -
	e->e->cam->up.y * e->e->cam->n.x);
	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 *
	e->e->cam->dist;
	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x *
	e->e->cam->dist, e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
	e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x *
	(e->e->cam->w / 2) - e->e->cam->up.x * (e->e->cam->h / 2),
	e->e->cam->c.y - e->e->cam->u.y *
	(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
	e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) -
	e->e->cam->up.z * (e->e->cam->h / 2));
}

void		keypress4(t_envg *e)
{
	e->e->cam->eye.y += 10;
	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	vnorm(&e->e->cam->n);
	e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z
	* e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
	e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
	e->e->cam->n.x);
	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 *
	e->e->cam->dist;
	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x *
	e->e->cam->dist,
	e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
	e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x *
	(e->e->cam->w / 2) - e->e->cam->up.x * (e->e->cam->h / 2),
	e->e->cam->c.y - e->e->cam->u.y * (e->e->cam->w / 2) - e->e->cam->up.y *
	(e->e->cam->h / 2),
	e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
	(e->e->cam->h / 2));
}

void		keypress5(t_envg *e)
{
	e->e->cam->eye.y -= 10;
	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	vnorm(&e->e->cam->n);
	e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z
	* e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
	e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
	e->e->cam->n.x);
	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 *
	e->e->cam->dist;
	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x *
	e->e->cam->dist, e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
	e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x *
	(e->e->cam->w / 2) - e->e->cam->up.x * (e->e->cam->h / 2),
	e->e->cam->c.y - e->e->cam->u.y * (e->e->cam->w / 2) - e->e->cam->up.y *
	(e->e->cam->h / 2), e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2)
	- e->e->cam->up.z * (e->e->cam->h / 2));
}

int			keypress(int key, t_envg *e)
{
	pthread_join(e->thread, NULL);
	if (key == ESC)
	{
		ft_exit(e);
		e->e->b_screen = 1;
	}
	if (key == 123)
// <<<<<<< HEAD
		keypress2(e);
	else if (key == 124)
		keypress3(e);
// =======
	// {
	// 	e->e->cam->eye.x += 10;
	// 	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	// 	vnorm(&e->e->cam->n);
	// 	e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
	// 	e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
	// 	e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
	// 	e->e->cam->n.x);
	// 	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
	// 	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	// 	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
	// 	e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
	// 	e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	// 	e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
	// 	e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
	// 	(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
	// 	e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
	// 	(e->e->cam->h / 2));
	// }
// 	else if (key == 124)
// 	{
// 		e->e->cam->eye.x -= 10;
// 		e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
// 		vnorm(&e->e->cam->n);
// 		e->e->cam->u = new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
// 		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
// 		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
// 		e->e->cam->n.x);
// 		e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
// 		e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
// 		e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
// 		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
// 		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
// 		e->e->cam->l = new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
// 		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
// 		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
// 		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) - e->e->cam->up.z *
// 		(e->e->cam->h / 2));
// 	}
// >>>>>>> master
	else if (key == 125)
		keypress4(e);
	else if (key == 126)
		keypress5(e);
	else
		return (1);
	pthread_create(&e->thread, NULL, ft_launch, e->e);
	return (1);
}
