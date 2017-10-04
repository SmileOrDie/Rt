/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_conf.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:25:09 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/22 19:04:35 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int	select_conf2_1(t_envg *e, int x, int y, int i)
{
	if (x > 40 && x < 60 && y > 400 + (i * 30) && y < 400 + (i * 30) + 20)
	{
		e->light = i;
		e->mod = 1;
		e->i_lst = 0;
		modif_light(e, i + e->page);
		return (1);
	}
	else if (x > 65 && x < 80 && y > 400 + (i * 30) && y < 400 + (i * 30) + 20)
	{
		del_elem(e, i + e->page);
		e->i_lst = 0;
		e->page = 0;
		conf_tab(e);
		return (1);
	}
	return (0);
}

static int	select_conf2_2(t_envg *e, int x, int y, int i)
{
	while (++i <= 26)
	{
		if (x > e->line_pos[i].w && x < e->line_pos[i].w + 40 &&
			y > e->line_pos[i].h && y < e->line_pos[i].h + 30)
			return (i);
	}
	if (x > 40 && x < 80 && y > 522 && y < 564)
		e->filter = (e->filter.blue == 0) ? (t_filter){1, 0, 0, 0, 0, 0} :
		(t_filter){0, 0, 0, 0, 0, 0};
	else if (x > 120 && x < 160 && y > 522 && y < 564)
		e->filter = (e->filter.green == 0) ? (t_filter){0, 1, 0, 0, 0, 0} :
	(t_filter){0, 0, 0, 0, 0, 0};
	else if (x > 200 && x < 240 && y > 522 && y < 564)
		e->filter = (e->filter.red == 0) ? (t_filter){0, 0, 1, 0, 0, 0} :
	(t_filter){0, 0, 0, 0, 0, 0};
	else if (x > 40 && x < 80 && y > 555 && y < 595)
		e->filter = (e->filter.sepia == 0) ? (t_filter){0, 0, 0, 1, 0, 0} :
	(t_filter){0, 0, 0, 0, 0, 0};
	else if (x > 120 && x < 160 && y > 555 && y < 595)
		e->filter = (e->filter.old == 0) ? (t_filter){0, 0, 0, 0, 1, 0} :
	(t_filter){0, 0, 0, 0, 0, 0};
	else if (x > 200 && x < 240 && y > 555 && y < 595)
		e->filter = (e->filter.cartoon == 0) ? (t_filter){0, 0, 0, 0, 0, 1} :
	(t_filter){0, 0, 0, 0, 0, 0};
	return (-1);
}

static void	select_conf_amb(t_envg *e, int x, int y)
{
	if (x > 160 && x < 177 && y > 624 && y < 648 && e->amb > 0.01)
		e->amb -= 0.01;
	else if (x > 243 && x < 260 && y > 624 && y < 648 && e->amb < 1.0)
		e->amb += 0.01;
}

static void	select_conf3(t_envg *e, int x, int y, int nb)
{
	if (x > 307 && x < 327 && y > 500 && y < 520 && nb > e->page + 3)
	{
		e->light = 1;
		e->i_lst = 0;
		e->page += 3;
	}
	else if (x < 297 && x > 277 && y > 500 && y < 520 && e->page > 0)
	{
		e->light = 1;
		e->page -= 3;
		e->i_lst = 0;
	}
	else if (x > 257 && x < 357 && y > 760 && y < 783)
	{
		creat_cam(e);
		e->i_lst = 0;
		home_tab(e);
	}
	else if (x > 48 && x < 70 && y > 624 && y < 648 && e->anti_a > 1)
	{
		e->anti_a--;
		e->win.w = e->win.w / (e->anti_a + 1) * e->anti_a;
		e->win.h = e->win.h / (e->anti_a + 1) * e->anti_a;
	}
	select_conf_amb(e, x, y);
}

int			select_conf2(t_envg *e, int x, int y)
{
	int				i;
	int				nb;
	t_parse_light	*b;

	b = e->parse_light;
	nb = 0;
	while (b)
	{
		nb++;
		b = b->next;
	}
	i = -1;
	while (++i < 3 && i < nb)
	{
		if (select_conf2_1(e, x, y, i))
			return (0);
	}
	select_conf3(e, x, y, nb);
	if (x > 91 && x < 113 && y > 624 && y < 648 && e->anti_a < 7)
	{
		e->anti_a++;
		e->win.h = e->win.h / (e->anti_a - 1) * e->anti_a;
		e->win.w = e->win.w / (e->anti_a - 1) * e->anti_a;
	}
	return (select_conf2_2(e, x, y, 18));
}
