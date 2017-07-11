/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_del_home_info.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:59:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 18:56:51 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void	select_del_1(t_envg *e, int x, int y)
{
	if (x > 255 && x < 355 && y > 765 && y < 790 &&
		e->e->nb_obj + 1 > e->page + 15)
	{
		e->page += 15;
		del_tab(e);
	}
	if (x > 55 && x < 155 && y > 765 && y < 790 && e->i_lst > 15 &&
		e->page > 0)
	{
		e->page -= 15;
		e->i_lst = e->page;
		del_tab(e);
	}
}

int			select_del(t_envg *e, int x, int y)
{
	int i;

	i = 0;
	while (i < 15 && i < e->e->nb_obj)
	{
		if (x > 40 && x < 60 && y > 200 + (i * 30) && y < 200 + (i * 30) + 20)
		{
			e->obj = i;
			e->light = -1;
			del_elem(e, i + e->page);
			e->i_lst = 0;
			e->page = 0;
			del_tab(e);
			return (0);
		}
		++i;
	}
	select_del_1(e, x, y);
	return (i);
}

int			select_info(t_envg *e, int x, int y)
{
	int i;

	i = 0;
	while (++i <= 2)
	{
		if (x > e->line_pos[i].w && x < e->line_pos[i].w + 317 &&
			y > e->line_pos[i].h && y < e->line_pos[i].h + 30)
			return (i + 40);
	}
	if (e->line[41][0] && x > 290 && x < 390 && y > 245 && y < 265)
		add_new_texture(e);
	else if (e->line[42][0] && x > 290 && x < 390 && y > 295 && y < 315)
		free_env_parse(e);
	else if (e->e->nb_obj > 0 && e->e->cam != NULL && x > 40 && x < 135 && y > 330 && y < 355)
		save_scene(e->e, NULL, -1);
	else if (e->e && e->e->mlx->img != NULL && x > 145 && x < 245 && y > 335 && y < 355)
		bmp_save_img(e);
	else
		info_tab(e);
	return (-1);
}

static void	select_home_1(t_envg *e, int x, int y)
{
	if (x > 255 && x < 355 && y > 765 &&
		y < 790 && e->e->nb_obj + 1 > e->page + 15)
	{
		e->page += 15;
		home_tab(e);
	}
	if (x > 55 && x < 155 && y > 765 && y < 790 && e->i_lst > 15)
	{
		e->page -= 15;
		e->i_lst = e->page;
		home_tab(e);
	}
}

int			select_home(t_envg *e, int x, int y)
{
	int i;

	i = -1;
	while (++i < 15)
	{
		if (x > 40 && x < 60 && y > 200 + (i * 30) && y < 200 + (i * 30) + 20)
		{
			e->obj = i + e->page;
			e->light = -1;
			modif_list(e, i + e->page);
			return (0);
		}
	}
	select_home_1(e, x, y);
	return (-1);
}
