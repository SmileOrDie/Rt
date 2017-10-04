/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_add.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:29:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 16:45:47 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int	select_obj(t_envg *e, int y)
{
	if (y >= 220 && y < 245)
		ft_strcpy(e->line[e->pos], "sphere");
	else if (y >= 245 && y < 268)
		ft_strcpy(e->line[e->pos], "plane");
	else if (y >= 268 && y < 292)
		ft_strcpy(e->line[e->pos], "cone");
	else if (y >= 292 && y < 316)
		ft_strcpy(e->line[e->pos], "cylinder");
	else if (y >= 316 && y < 339)
		ft_strcpy(e->line[e->pos], "light");
	else if (y >= 339 && y < 363)
		ft_strcpy(e->line[e->pos], "circle");
	else if (y >= 363 && y < 387)
		ft_strcpy(e->line[e->pos], "square");
	else if (y >= 387 && y < 412)
		ft_strcpy(e->line[e->pos], "cube");
	else if (y >= 412 && y < 436)
		ft_strcpy(e->line[e->pos], "cone_l");
	else if (y >= 436 && y < 465)
		ft_strcpy(e->line[e->pos], "cylinder_l");
	(e->volet.add == 1) ? add_tab(e) : conf_tab(e);
	return (e->pos);
}

static int	select_add_3(t_envg *e, int x, int y, int *i)
{
	while (*i <= 2)
	{
		if (x > e->line_pos[*i].w && x < e->line_pos[*i].w + 317 &&
			y > e->line_pos[*i].h && y < e->line_pos[*i].h + 30)
			return (*i);
		*i += 1;
	}
	while (*i <= 15)
	{
		if (x > e->line_pos[*i].w && x < e->line_pos[*i].w + 40 &&
			y > e->line_pos[*i].h && y < e->line_pos[*i].h + 30)
			return (*i);
		*i += 1;
	}
	return (0);
}

static int	select_add_2(t_envg *e, int x, int y, int i)
{
	while (i < 3)
	{
		if (x > 40 && x < 60 && y > 600 + (i * 30) && y < 620 + (i * 30))
		{
			i = (unsigned char)i + 1 + e->page;
			e->line[30][0] = (e->line[30][0] == i) ? 0 : i;
			e->volet.add == 0 ? conf_tab(e) : add_tab(e);
			return (16);
		}
		i++;
	}
	if (x > 160 && x < 180 && y > 490 && y < 510)
		e->line[30][1] = (e->line[30][1] == 1) ? 0 : 1;
	else if (e->page > 2 && x > 50 && x < 150 && y > 715 && y < 736)
		e->page -= 3;
	else if (e->page + 3 < e->nb_tex && x > 258 && x < 356 && y > 715 &&
		y < 736)
		e->page += 3;
	e->volet.add == 0 ? conf_tab(e) : add_tab(e);
	return (0);
}

static int	select_add_1(t_envg *e, int x, int y, int i)
{
	t_parse_obj *b;

	if (e->pos == 1 && x > e->line_pos[e->pos].w &&
		x < e->line_pos[e->pos].w + 317 && y > e->line_pos[e->pos].h)
		return (select_obj(e, y));
	if (select_add_3(e, x, y, &i) != 0)
		return (i);
	if (x > e->line_pos[31].w && x < e->line_pos[31].w + 40 &&
			y > e->line_pos[31].h && y < e->line_pos[31].h + 30)
		return (31);
	i = 0;
	b = e->parse_obj;
	while (b)
	{
		if (b->obj.id == e->obj + e->page)
			break ;
		b = b->next;
	}
	if (select_add_2(e, x, y, i) == 16)
		return (16);
	return (16);
}

int			select_add(t_envg *e, int x, int y)
{
	int i;

	i = select_add_1(e, x, y, 0);
	if (i <= 15 || i == 31)
		return (i);
	else if (x > e->line_pos[30].w && x < e->line_pos[30].w + 100 &&
		y > e->line_pos[30].h && y < e->line_pos[30].h + 50)
	{
		e->error = check_var_obj(e->line);
		e->pos = i;
		if (e->volet.add == 1 && e->error == -1)
			creat_elem(e);
		else if (e->mod == 1 && e->volet.conf == 1 && e->error == -1)
		{
			creat_elem(e);
			(e->light == -1) ?
			del_elem(e, e->obj) : del_elem(e, e->light + e->page);
		}
		e->i_lst = 0;
		e->page = 0;
		home_tab(e);
		return (i);
	}
	return (-1);
}
