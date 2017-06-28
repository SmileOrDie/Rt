/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_mouse2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:41:12 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 16:26:38 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			mousse_click_x(t_envg *e, int x)
{
	e->page = 0;
	e->i_lst = 0;
	re_init_tab(e);
	if (x > 25 && x <= 75)
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
		info_tab(e);
	else
		e->i_lst = 0;
	e->pos = (x > 75 && x < 135) ? add_tab(e) : e->pos;
}

int				select_pos(t_envg *e, int x, int y)
{
	int i;

	i = 0;
	if (e->volet.add == 1)
		return (select_add(e, x, y));
	else if (e->volet.conf == 1)
		return (select_conf(e, x, y));
	else if (e->volet.info == 1)
		return (select_info(e, x, y));
	else if (e->volet.del == 1)
		return (select_del(e, x, y));
	else if (e->volet.home == 1)
		return (select_home(e, x, y));
	return (-1);
}

void			volet_target2(t_envg *e)
{
	e->f_key = 1;
	(e->pos == 1) ? load_img(e, e->pos_value[16]) :
	load_img(e, e->pos_value[e->pos] + 1);
	if (e->pos > 2 && (e->pos <= 15 || e->pos == 31))
		print_line(e, e->pos, 3);
	else
		print_line(e, e->pos, 30);
}

void			volet_target3(t_envg *e)
{
	e->f_key = 1;
	(e->pos == 1) ? load_img(e, e->pos_value[16]) :
	load_img(e, e->pos_value[e->pos] + 1);
	if (((e->pos > 2 && e->pos <= 15) || e->pos == 31) || (e->pos >= 19 \
		&& e->pos <= 26))
		print_line(e, e->pos, 3);
	else
		print_line(e, e->pos, 30);
}

void			volet_target(t_envg *e)
{
	if (e->volet.add == 1 && ((e->pos > 0 && e->pos <= 15) || e->pos == 31))
		volet_target2(e);
	else if (e->volet.conf == 1 && (((e->pos > 0 && e->pos <= 15) || \
	e->pos == 31) ||
		(e->pos >= 19 && e->pos <= 26)))
		volet_target3(e);
	else if (e->volet.info == 1 && e->pos > 40 && e->pos <= 42)
	{
		e->f_key = 1;
		e->pos -= 40;
		load_img(e, e->pos_value[e->pos] + 1);
		e->pos += 40;
		print_line(e, e->pos, 30);
	}
	else
	{
		e->f_key = 0;
		e->pos = 0;
	}
}
