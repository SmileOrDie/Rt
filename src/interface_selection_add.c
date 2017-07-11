/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_add.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:29:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 19:59:28 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

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

static int	select_add_3(t_envg *e, t_norme n)
{
	if (e->page > 2 && n.x > 50 && n.x < 100 && n.y > 715 && n.y < 736)
		e->page -= 3;
	else if (e->page + 3 < e->e->nb_tex && n.x > 258 && n.x < 356 && n.y > 715\
		&& n.y < 736)
		e->page += 3;
	e->volet.add == 0 ? conf_tab(e) : add_tab(e);
	return (16);
}

static int	select_add_2(t_envg *e, t_norme n)
{
	n.i = 0;
	n.b = e->e->parse_obj;
	while (n.b)
	{
		if (n.b->obj.id == e->obj + e->page)
			break ;
		n.b = n.b->next;
	}
	while (n.i < 3)
	{
<<<<<<< HEAD
		if (n.x > 40 && n.x < 60 && n.y > 600 + (n.i * 30) && n.y < 620 + \
		(n.i * 30))
		{
			n.b->obj.id_texture = (n.b->obj.id_texture == \
				(unsigned char)n.i + 1) ? 0 : (unsigned char)n.i + 1 + e->page;
			e->line[30][0] = n.b->obj.id_texture;
=======
		if (x > 40 && x < 60 && y > 600 + (i * 30) && y < 620 + (i * 30))
		{
			i = (unsigned char)i + 1 + e->page;
			e->line[30][0] = (e->line[30][0] == i) ? 0 : i;
>>>>>>> master
			e->volet.add == 0 ? conf_tab(e) : add_tab(e);
			return (16);
		}
		n.i++;
	}
<<<<<<< HEAD
	return (select_add_3(e, n));
}

static int	select_add_1(t_envg *e, int x, int y, int i)
{
	t_norme		n;

	n.x = x;
	n.y = y;
	n.i = i;
	if (e->pos == 1 && n.x > e->line_pos[e->pos].w && n.x < \
		e->line_pos[e->pos].w + 317 && n.y > e->line_pos[e->pos].h)
		return (select_obj(e, n.y));
	while (++n.i <= 2)
	{
		if (n.x > e->line_pos[n.i].w && n.x < e->line_pos[n.i].w + 317 &&
			n.y > e->line_pos[n.i].h && n.y < e->line_pos[n.i].h + 30)
			return (n.i);
	}
	while (n.i <= 15)
	{
		if (n.x > e->line_pos[n.i].w && n.x < e->line_pos[n.i].w + 40 &&
			n.y > e->line_pos[n.i].h && n.y < e->line_pos[n.i].h + 30)
			return (n.i);
		n.i++;
	}
	if (n.x > e->line_pos[31].w && n.x < e->line_pos[31].w + 40 &&
			n.y > e->line_pos[31].h && n.y < e->line_pos[31].h + 30)
		return (31);
	return (select_add_2(e, n));
=======
	if (x > 160 && x < 180 && y > 490 && y < 510)
		e->line[30][1] = (e->line[30][1] == 1) ? 0 : 1;
	else if ( e->page > 2 && x > 50 && x < 100 && y > 715 && y < 736)
		e->page -= 3;
	else if (e->page + 3  < e->e->nb_tex && x > 258 && x < 356 && y > 715 && y < 736)
		e->page += 3;
	e->volet.add == 0 ? conf_tab(e) : add_tab(e);
	return (16);
>>>>>>> master
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
			del_elem(e, e->obj + e->page) : del_elem(e, e->light + e->page);
		}
		e->i_lst = 0;
		e->page = 0;
		home_tab(e);
		return (i);
	}
	return (-1);
}
