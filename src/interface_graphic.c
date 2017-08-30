/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:52:30 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/02 13:23:10 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int		interface_redcross(t_envg *e)
{
	(void)e;
	exit(1);
	return (1);
}

void			run_first(t_envg *e)
{
	load_img(e, 0);
	re_init_tab(e);
	home_tab(e);
	e->mod = 1;
	e->f_key = 0;
	e->e->wait = 0;
	e->font = 1;
	e->volet = (t_tab_valid){1, 0, 0, 0, 0};
	modif_default(e);
}

static void		event_touch(t_envg *e)
{
	mlx_hook(e->mlx.win, 2, 0, &interface_keypress, e);
	mlx_hook(e->mlx.win, 17, 0, &interface_redcross, e);
	mlx_hook(e->mlx.win, 4, 0, &interface_mouse_click, e);
}

int				put_imag(t_env *e)
{
	t_pos l;

	l = e->anti_a ? (t_pos){e->win.w / e->anti_a, e->win.h / e->anti_a} :
(t_pos){0, 0};
	if (e->wait < 5 && e->wait != 0)
	{
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->wait_img[e->
wait - 1],
		(l.w / 2) - (e->size[e->wait - 1].w / 2), (l.h / 2) - (e->size[e->
wait - 1].h / 2));
		e->wait = 0;
	}
	else if (e->wait == 5)
	{
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
		e->wait = 0;
	}
	return (0);
}

void			graphic_interface(t_envg *e)
{
	init_envg(e, e->e);
	init_mlx(e);
	(e->font == 0) ? run_first(e) : 0;
	event_touch(e);
	mlx_loop_hook(e->mlx.mlx, put_imag, e->e);
	mlx_loop(e->mlx.mlx);
}
