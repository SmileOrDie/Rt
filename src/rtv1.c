/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/24 12:00:02 by shamdani         ###   ########.fr       */
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
	e->nb_thread = 1;
}

void			init_mlx(t_env *e)
{
	if (!(e->mlx->mlx = mlx_init()))
		ft_error(MLX,
			"static int	init_mlx(t_env *e) (=>mlx_init())-(rtv1.c))");
	else if (!(e->mlx->win =
		mlx_new_window(e->mlx->mlx, e->mlx->w / 4, e->mlx->h / 4, "rtv1")))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_window())-(rtv1.c))");
	else if (!(e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->w, e->mlx->h)))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_image())-(rtv1.c))");
	else if (!(e->mlx->img4 = mlx_new_image(e->mlx->mlx, e->mlx->w / 4, e->mlx->h / 4)))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_image())-(rtv1.c))");
	else if (!(e->mlx->data4 = (unsigned char*)mlx_get_data_addr(e->mlx->img4, &(e->mlx->bpp),
		&(e->mlx->sizeline), &(e->mlx->endian))))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_get_data_addr())-(rtv1.c))");
	else if (!(e->mlx->data = (unsigned char*)mlx_get_data_addr(e->mlx->img, &(e->mlx->bpp),
		&(e->mlx->sizeline), &(e->mlx->endian))))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_get_data_addr())-(rtv1.c))");
}

static void		select_opt(char **av, t_env *e)
{
	t_timex t;

	if (ft_strchr(av[2], 't') != NULL)
		t.total_f = 1;
	else
		t.total_f = 0;
	if (ft_strchr(av[2], 'p') != NULL)
		t.pars_f = 1;
	else
		t.pars_f = 0;
	if (ft_strchr(av[2], 'r') != NULL)
		t.ray_f = 1;
	else
		t.ray_f = 0;
	e->chrono = &t;
	time_mode(av[1],e);
}	

static void		event_touch(t_env *e)
{
	mlx_hook(e->mlx->win, 2, 0, &keypress, e);
	mlx_hook(e->mlx->win, 17, 0, &redcross, e);
}

int				main(int ac, char **av)
{
	t_env		e;

	if (ac == 2 || ac == 3)
	{
		init(&e);
		if (ac == 3)
			select_opt(av, &e);
		else
		{
			ft_parse(av[1], &e);
			init_mlx(&e);
			pthread_ray(&e);
		}
		event_touch(&e);
		mlx_loop(e.mlx->mlx);
	}
	else
		ft_error(NUMBER_ARG, "rtv1 [Path of file]");
	return (1);
}
