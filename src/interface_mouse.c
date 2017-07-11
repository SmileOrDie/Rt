/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:01:00 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/11 16:23:54 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void		ft_exit(t_envg *e)
{
	pthread_cancel(e->thread);
	if (e->e->mlx->img)
		mlx_destroy_image(e->e->mlx->mlx, e->e->mlx->img);
	if (e->e->mlx->win)
		mlx_destroy_window(e->e->mlx->mlx, e->e->mlx->win);
	e->e->mlx->img = NULL;
	e->e->mlx->win = NULL;
	e->run = 0;
}

void		init_mlx1(t_envg *e)
{
	if (!(e->e->mlx->win =
		mlx_new_window(e->e->mlx->mlx, e->e->mlx->w / e->e->anti_a, \
			e->e->mlx->h / e->e->anti_a, "rtv1")))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_window())-(rtv1.c))");
	else if (!(e->e->mlx->img = mlx_new_image(e->e->mlx->mlx, e->e->mlx->w / \
		e->e->anti_a, e->e->mlx->h / e->e->anti_a)))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_image())-(rtv1.c))");
	else if (!(e->e->mlx->data = mlx_get_data_addr(e->e->mlx->img, \
		&(e->e->mlx->bpp),
		&(e->e->mlx->sizeline), &(e->e->mlx->endian))))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_get_data_addr())-(rtv1.c))");
	e->e->filter_t = NULL;
	e->filter.old == 1 ? e->e->filter_t = &filter_blur : 0;
	e->filter.sepia == 1 ? e->e->filter_t = &filter_sepia : 0;
	e->filter.blue == 1 ? e->e->filter_t = &filter_blue : 0;
	e->filter.green == 1 ? e->e->filter_t = &filter_green : 0;
	e->filter.red == 1 ? e->e->filter_t = &filter_red : 0;
}

void		event_touch(t_envg *e)
{
	mlx_hook(e->e->mlx->win, 2, 0, &keypress, e);
	mlx_hook(e->e->mlx->win, 17, 0, &redcross, e->e);
}
