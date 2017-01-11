/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 15:17:41 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		init(t_env *e)
{
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error(MALLOC, "int	ft_parse(char *name, t_env *e)(e->mlx)");
	e->light = NULL;
	e->d_light = NULL;
	e->obj = NULL;
	e->cam = NULL;
	e->mlx->w = W;
	e->mlx->h = H;
	e->amb = 0.1;
}

static void		init_mlx(t_env *e)
{
	if (!(e->mlx->mlx = mlx_init()))
		ft_error(MLX,
			"static int	init_mlx(t_env *e) (=>mlx_init())-(rtv1.c))");
	else if (!(e->mlx->win =
		mlx_new_window(e->mlx->mlx, e->mlx->w, e->mlx->h, "rtv1")))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_window())-(rtv1.c))");
	else if (!(e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->w, e->mlx->h)))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_image())-(rtv1.c))");
	else if (!(e->mlx->data = mlx_get_data_addr(e->mlx->img, &(e->mlx->bpp),
		&(e->mlx->sizeline), &(e->mlx->endian))))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_get_data_addr())-(rtv1.c))");
}

static void		event_touch(t_env *e)
{
	mlx_hook(e->mlx->win, 2, 0, &keypress, e);
	mlx_hook(e->mlx->win, 17, 0, &redcross, e);
}

int				main(int ac, char **av)
{
	t_env		e;

	if (ac == 2)
	{
		init(&e);
		ft_parse(av[1], &e);
		init_mlx(&e);
		start_ray(&e);
		event_touch(&e);
		mlx_loop(e.mlx->mlx);
	}
	else
		ft_error(NUMBER_ARG, "rtv1 [Path of file]");
	return (1);
}
