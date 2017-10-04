/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:01:43 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/13 16:44:30 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int	interface_keypress_1(t_envg *e)
{
	if (e->volet.add == 1)
	{
		creat_elem(e);
		e->i_lst = 0;
		e->page = 0;
		home_tab(e);
	}
	else if (e->volet.conf == 1 && e->mod == 1)
	{
		creat_elem(e);
		(e->light == -1) ? del_elem(e, e->obj + e->page) :
			del_elem(e, e->light + e->page);
		e->i_lst = 0;
		e->page = 0;
		home_tab(e);
	}
	else if (e->volet.info == 1 && e->pos == 41 && e->line[e->pos][0] != '\0')
		add_new_texture(e);
	else if (e->volet.info == 1 && e->pos == 42 && e->line[e->pos][0] != '\0')
		free_env_parse(e);
	return (1);
}

void		interface_keypress_2_2(int **val, char *li, char *pr)
{
	**val = 3;
	add_line(li, pr, 1);
}

static int	interface_keypress_2(int key, t_envg *e, int *val, char *li)
{
	char	*pr;
	int		pression;

	pression = 0;
	e->volet.info == 1 ? info_tab(e) : 0;
	pr = ft_print_key(key, e);
	if (!(ft_strcmp(pr, "right delete")) || !(ft_strcmp(pr, "delete")))
	{
		*val = ((e->pos < 40 && e->pos > 42) || (e->pos > 2 && e->pos <= 15) ||
			e->pos == 31 || (e->pos >= 19 && e->pos <= 26)) ? 3 : 30;
		del_line(e);
	}
	else if (!(ft_strcmp(pr, "return")) || !(ft_strcmp(pr, "enter")))
		pression = interface_keypress_1(e);
	else if (((e->pos > 2 && e->pos <= 15) || e->pos == 31 ||
		(e->pos >= 19 && e->pos <= 26)))
		interface_keypress_2_2(&val, li, pr);
	else if (e->pos == 2 || (e->pos > 40 && e->pos <= 42))
	{
		*val = 30;
		add_line(li, pr, 0);
	}
	return (pression);
}

static int	exeption_key(int key)
{
	if ((key >= 123 && key <= 126) || key == 81 || key == 75 || key == ESC)
		return (1);
	if (key == 260 || key == 262 || key == 269 || key == 279 || key == 115)
		return (1);
	if (key == 116 || key == 117 || key == 119 || key == 121 || key == 71)
		return (1);
	return (0);
}

int			interface_keypress(int key, t_envg *e)
{
	char	*line;
	int		val;
	int		pression;

	line = e->line[e->pos];
	val = 0;
	if (e->f_key && exeption_key(key))
		return (1);
	else if (e->f_key)
	{
		(key == 48 && e->volet.info == 1) ? switch_tabul(e) : 0;
		pression = interface_keypress_2(key, e, &val, line);
		e->volet.info == 1 ? e->pos -= 40 : 0;
		pression == 0 ? load_img(e, e->pos_value[e->pos] + 1) : 0;
		e->volet.info == 1 ? e->pos += 40 : 0;
		print_line(e, e->pos, val);
	}
	return (1);
}
