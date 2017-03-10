/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesprog <ldesprog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/03/10 17:03:43 by ldesprog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		init(t_env *e)
{
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error(MALLOC, "int	ft_parse(char *name, t_env *e)(e->mlx)");
	e->light = NULL;
	e->l_obj = NULL;
	e->cam = NULL;
	e->mlx->w = W;
	e->mlx->h = H;
	e->amb = 0.1;
	e->nb_obj = 0;
	e->nb_light = 0;
	e->move = 0;
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

t_env			*ft_create_tab_env(t_env e)
{
	t_env *tab;
	int i;

	tab = (t_env *)malloc(sizeof(t_env) * e.mlx->h);
	i = 0;
	while (i < e.mlx->h)
	{
		tab[i].amb = e.amb;
		tab[i].nb_obj = e.nb_obj;
		tab[i].nb_light = e.nb_light;
		i++;
	}
	return (tab);

}

int				main(int ac, char **av)
{
	t_env		e;
	int			nb_source;
	t_env 		*tab_env;

	e.cl = (t_opencl *)malloc(sizeof(t_opencl));
	// secure
	if (ac == 2)
	{
		init(&e);
		ft_parse(av[1], &e);
		init_mlx(&e);
		tab_env = ft_create_tab_env(e);
		nb_source = 7;
		ft_init_opencl(&e, e.cl, nb_source, tab_env);
		ft_launch_calc(&e, e.cl);
		event_touch(&e);
		mlx_loop(e.mlx->mlx);
	}
	else
		ft_error(NUMBER_ARG, "rtv1 [Path of file]");
	return (1);
}
