/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_del_home_info.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:59:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 13:54:16 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int 		srch_id(t_envg *e, int pos)
{
	t_parse_obj	*b;
	int			i;

	i = 0;
	b = e->parse_obj;
	while (b->next && i != pos)
	{
		b = b->next;
		i++;
	}
	return (b->obj.id);
}

static void	select_del_1(t_envg *e, int x, int y)
{
	if (x > 255 && x < 355 && y > 765 && y < 790 &&
		e->nb_obj + 1 > e->page + 15)
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
	while (i < 15 && i < e->nb_obj)
	{
		if (x > 40 && x < 60 && y > 200 + (i * 30) && y < 200 + (i * 30) + 20)
		{
			e->obj = srch_id(e, i + e->page);
			e->light = -1;
			del_elem(e, e->obj);
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
	else if (e->nb_obj > 0 && e->cam.set && x > 40 && x < 135 &&
		y > 330 && y < 355)
	{
		save_scene(e, NULL, -1);
		home_tab(e);		
	}
	else if (e->e && e->e->mlx.img != NULL && x > 145 && x < 245 && y > 335
		&& y < 355)
	{
		bmp_save_img(e);
		home_tab(e);
	}
	else
		info_tab(e);
	return (-1);
}

static void	select_home_1(t_envg *e, int x, int y)
{
	if (x > 255 && x < 355 && y > 765 &&
		y < 790 && e->nb_obj + 1 > e->page + 15)
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
	while (++i < 15 && i < e->nb_obj)
	{
		if (x > 40 && x < 60 && y > 200 + (i * 30) && y < 200 + (i * 30) + 20)
		{
			e->obj = srch_id(e, i + e->page);
			e->light = -1;
			e->page = 0;
			e->mod = 1;
			//a faire.
			modif_list(e, e->obj);
			return (0);
		}
	}
	select_home_1(e, x, y);
	return (-1);
}
