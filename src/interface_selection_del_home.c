/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_del_home.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:59:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 13:54:16 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int			srch_id(t_envg *e, int pos)
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
			modif_list(e, e->obj);
			return (0);
		}
	}
	select_home_1(e, x, y);
	return (-1);
}
