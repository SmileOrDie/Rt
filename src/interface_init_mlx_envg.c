/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init_mlx_envg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:49:39 by phmoulin          #+#    #+#             */
/*   Updated: 2017/11/08 17:49:14 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			re_init_tab(t_envg *e)
{
	int i;

	i = 5;
	while (i)
		load_img(e, i--);
}

static void		init_envg2(t_envg *e, t_env *env)
{
	e->mlx.w = WI;
	e->mlx.h = HE;
	e->f_key = 0;
	e->font = 0;
	e->e = env;
	e->page = 0;
	e->i_lst = 0;
	e->shift = 1;
	e->pos = 0;
	e->run = 0;
	e->filter = (t_filter){0, 0, 0, 0, 0, 0};
	e->error = -1;
	e->parse_obj = NULL;
	e->parse_light = NULL;
}

void			init_envg(t_envg *e, t_env *env)
{
	int i;

	i = 0;
	init_envg2(e, env);
	if (!(e->line = (char**)malloc(sizeof(char*) * LINE_SIZE + 1)))
		return ;
	while (i < LINE_SIZE)
	{
		if (!(e->line[i] = (char*)malloc(sizeof(char) * LINE_SIZE + 1)))
			return ;
		bzero(e->line[i++], LINE_SIZE);
	}
	init_line_pos(e);
	init_pos_value(e);
}

static void		init_mlx_2(t_envg *e)
{
	e->wait_img[0] = NULL;
	e->wait_img[1] = NULL;
	e->wait_img[2] = NULL;
	e->wait_img[3] = NULL;
	if (!(e->wait_img[0] = mlx_xpm_file_to_image(e->mlx.mlx,
		"./xpm_file/load_10.xpm", &e->size[0].w, &e->size[0].h)))
		ft_error("wait_img[0] :", "load failed");
	if (!(e->wait_img[1] = mlx_xpm_file_to_image(e->mlx.mlx,
		"./xpm_file/load_30.xpm", &e->size[1].w, &e->size[1].h)))
		ft_error("wait_img[1] :", "load failed");
	if (!(e->wait_img[2] = mlx_xpm_file_to_image(e->mlx.mlx,
		"./xpm_file/load_50.xpm", &e->size[2].w, &e->size[2].h)))
		ft_error("wait_img[2] :", "load failed");
	if (!(e->wait_img[3] = mlx_xpm_file_to_image(e->mlx.mlx,
		"./xpm_file/load_80.xpm", &e->size[3].w, &e->size[3].h)))
		ft_error("wait_img[3] :", "load failed");
}

void			init_mlx(t_envg *e)
{
	e->img.img = NULL;
	if (!(e->mlx.mlx = mlx_init()))
		return ;
	else if (!(e->mlx.win =
		mlx_new_window(e->mlx.mlx, e->mlx.w, e->mlx.h,
			"Graphical interface by BIM")))
		return ;
	else if (!(e->mlx.img = mlx_new_image(e->mlx.mlx, e->mlx.w,
		e->mlx.h)))
		return ;
	else if (!(e->mlx.data = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp),
		&(e->mlx.sizeline), &(e->mlx.endian))))
		return ;
	init_mlx_2(e);
}
