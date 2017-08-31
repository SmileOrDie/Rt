/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:01:00 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/30 16:25:30 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_env	g_env_default = {(t_mlx){NULL, NULL, NULL, NULL, 4, 0, 0, W, H, 0, 0},
	NULL, NULL, NULL, NULL, (t_cam){{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
		0, 0, 0, 0, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0
	}, 0, 0, 1, 0, NULL, 0, 0, 1, 1, {0, 0, 0}, NULL, 0, 1, {W, H}, NULL,
	NULL, NULL, 0, 0, 0, NULL};

static void		init_variable(t_envg *e)
{
	e->run = 1;
	*(e->e) = g_env_default;
	e->e->cam = e->cam;
	e->e->nb_tex = e->nb_tex;
	e->e->anti_a = e->anti_a;
	e->e->filter_t = NULL;
	e->e->flag = 1;
	e->e->wait = 1;
	e->filter.old == 1 ? e->e->filter_t = &filter_blur : 0;
	e->filter.sepia == 1 ? e->e->filter_t = &filter_sepia : 0;
	e->filter.blue == 1 ? e->e->filter_t = &filter_blue : 0;
	e->filter.green == 1 ? e->e->filter_t = &filter_green : 0;
	e->filter.red == 1 ? e->e->filter_t = &filter_red : 0;
	e->e->group_max = e->group_max;
	e->e->cl_e = e->cl_e;
	e->e->cl_e->amb = e->amb * 100;
	e->e->cl_e->group_max = e->group_max;
}

static void		init_mlx_raytrace(t_envg *e)
{
	e->e->mlx.mlx = e->mlx.mlx;
	e->e->win = e->win;
	e->e->wait_img = e->wait_img;
	e->e->size = e->size;
	if (!(e->e->mlx.win = mlx_new_window(e->e->mlx.mlx, e->e->win.w /
			e->e->anti_a, e->e->win.h / e->e->anti_a, "Raytrace")))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_window())-(rt.c))");
	else if (!(e->e->mlx.img = mlx_new_image(e->e->mlx.mlx, e->e->win.w /
			e->e->anti_a, e->e->win.h / e->e->anti_a)))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_new_image())-(rt.c))");
	else if (!(e->e->mlx.data = mlx_get_data_addr(e->e->mlx.img,
			&(e->e->mlx.bpp), &(e->e->mlx.sizeline), &(e->e->mlx.endian))))
		ft_error(MLX,
			"static int init_mlx(t_env *e) (=>mlx_get_data_addr())-(rt.c))");
	mlx_hook(e->e->mlx.win, 2, 0, &keypress, e);
	mlx_hook(e->e->mlx.win, 17, 0, &redcross, e->e);
}

static void		interface_mouse_click_3(t_envg *e)
{
	init_id(e);
	if (e->run == 1)
	{
		pthread_join(e->thread, NULL);
		e->thread = NULL;
		ft_exit(e);
	}
	if (e->cam.view == 0)
	{
		init_variable(e);
		init_mlx_raytrace(e);
		ft_creat_lst_obj(e);
		ft_get_image_texture(e);
		pthread_create(&e->thread, NULL, ft_launch, e->e);
	}
}

static void		interface_mouse_click_2(t_envg *e, int x, int y)
{
	if (y > 125 && y < 150)
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
	else if (y > 830 && y < 900 && e->volet.home == 1 && (e->nb_obj > 0
		&& e->cam.set != 0))
		interface_mouse_click_3(e);
}

int				interface_mouse_click(int button, int x, int y, t_envg *e)
{
	if (button == 1)
	{
		if (e->error != -1)
			return (error_gestion(e, x, y));
		interface_mouse_click_2(e, x, y);
		e->pos = select_pos(e, x, y);
		if (e->volet.add == 1 && (((e->pos > 0 && e->pos <= 15) || e->pos == 31)
			|| e->pos == -1))
			e->pos = add_tab(e);
		else if (e->volet.conf == 1 && ((((e->pos > 0 && e->pos <= 15) ||
			e->pos == 31) || (e->pos >= 19 && e->pos <= 26)) || e->pos == -1))
		{
			e->i_lst = 0;
			e->pos = conf_tab(e);
		}
		else if (e->volet.info == 1 && e->pos > 40 && e->pos < 43)
			info_tab(e);
		volet_target(e);
	}
	return (1);
}
