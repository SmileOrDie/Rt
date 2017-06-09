/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:01:00 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/21 16:08:15 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int		select_pos(t_envg *e, int x, int y)
{
	int i;

	i = 0;
	if (e->volet.add == 1)
		return (select_add(e, x, y));
	else if (e->volet.conf == 1)
		return (select_conf(e, x, y));
	else if (e->volet.other == 1)
		return (select_info(e, x, y));
	else if (e->volet.del == 1) 
		return (select_del(e, x, y));
	else if (e->volet.home == 1)
		return (select_home(e, x, y));
	return (-1);
}

static void		volet_target(t_envg *e)
{
	if (e->volet.add == 1 && e->pos > 0 && e->pos <= 15)
	{
		e->f_key = 1;
		(e->pos == 1) ? load_img(e, e->pos_value[16]) :
		load_img(e, e->pos_value[e->pos] + 1);
		if (e->pos > 2 && e->pos <= 15)
			print_line(e, e->pos, 3);
		else
			print_line(e, e->pos, 30);
	}
	else if (e->volet.conf == 1 && ((e->pos > 0 && e->pos <= 15) ||
		(e->pos >= 19 && e->pos <= 26)))
	{
		e->f_key = 1;
		(e->pos == 1) ? load_img(e, e->pos_value[16]) :
		load_img(e, e->pos_value[e->pos] + 1);
		if ((e->pos > 2 && e->pos <= 15) || (e->pos >= 19 && e->pos <= 26))
			print_line(e, e->pos, 3);
		else
			print_line(e, e->pos, 30);
	}
	else
		e->f_key = 0;
}

static void		mousse_click_x(t_envg *e, int x)
{
	e->page = 0;
	e->i_lst = 0;
	re_init_tab(e);
	if (x > 25 && x < 75)
	{
		e->mod = 1;
		home_tab(e);
	}
	else if (x > 135 && x < 195)
	{
		e->mod = 0;
		e->light = 0;
		conf_tab(e);
	}
	else if (x > 195 && x < 255)
		del_tab(e);
	else if (x > 255 && x < 315)
	{
		load_img(e, 5);
		e->volet = (t_tab_valid){0, 0, 0, 0, 1};
	}
	e->pos = (x > 75 && x < 135) ? add_tab(e) : e->pos;
}

void	ft_exit(t_envg *e)
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

static void		init_mlx1(t_env *e)
{
	if (!(e->mlx->win =
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

static void		event_touch(t_envg *e)
{
	mlx_hook(e->e->mlx->win, 2, 0, &keypress, e);
	mlx_hook(e->e->mlx->win, 17, 0, &redcross, e->e);
}

int				interface_mouse_click(int button, int x, int y, t_envg *e)
{
	if (button == 1)
	{
		if (e->error != -1)
			return (error_gestion(e, x, y));
		else if (y > 125 && y < 150)
		{
			if (x > 25 && x < 315)
				mousse_click_x(e, x);
			else
			{
				e->f_key = 0;
				e->i_lst = 0;
				e->mod = 0;
			}
		}
		else if (y > 830 && y < 900 && e->volet.home == 1 && (e->e->nb_obj > 0 && e->e->cam != NULL))
		{
			if (e->run == 1)
			{
				pthread_join(e->thread, NULL);
				e->thread = NULL;
				ft_exit(e);
			}
			e->run = 1;
			init_mlx1(e->e);
			event_touch(e);
			pthread_create(&e->thread, NULL, ft_launch, e->e);
		}
		e->pos = select_pos(e, x, y);
		if (e->volet.add == 1 && ((e->pos > 0 && e->pos <= 15) || e->pos == -1))
			e->pos = add_tab(e);
		else if (e->volet.conf == 1 && (((e->pos > 0 && e->pos <= 15) ||
			(e->pos >= 19 && e->pos <= 26)) || e->pos == -1))
		{
			e->i_lst = (e->light == -1) ? 0 : e->i_lst;
			e->pos = conf_tab(e);
		}
		volet_target(e);
	}
	return (1);
}
