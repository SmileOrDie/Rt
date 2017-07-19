/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:09:03 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/16 19:21:27 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int				add_tab(t_envg *e)
{
	int save;
	int i;

	i = 0;
	save = e->pos;
	e->volet = (t_tab_valid) {0, 1, 0, 0, 0};
	load_img(e, 2);
	e->f_key = 0;
	while (i <= 15)
	{
		e->pos = i;
		load_img(e, e->pos_value[i]);
		print_line(e, i, (i > 2) ? 3 : 30);
		if (i == 15)
		{
			e->pos = 31;
			load_img(e, e->pos_value[e->pos]);
			print_line(e, e->pos, 3);
		}
		i++;
	}
	load_img(e, 29);
	e->pos = 30;
	load_img(e, e->pos_value[e->pos]);
	return ((save == -1) ? 0 : save);
}

int				conf_tab(t_envg *e)
{
	int		i;
	int		save;

	i = 0;
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	save = e->pos;
	load_img(e, 3);
	conf_tab3(e, i);
	load_img(e, 20);
	return ((save == -2) ? 0 : save);
}

void			home_tab(t_envg *e)
{
	t_parse_obj *b;

	b = e->e->parse_obj;
	e->e->nb_obj = 0;
	if (b)
		while (b)
		{
			e->e->nb_obj++;
			b = b->next;
		}
	e->volet = (t_tab_valid) {1, 0, 0, 0, 0};
	e->f_key = 0;
	load_img(e, 1);
	load_img(e, 15);
	(e->i_lst > 15) ? load_img(e, 16) : 0;
	(e->e->nb_obj > e->page + 15) ? load_img(e, 17) : 0;
	(e->e->nb_obj > 0 && e->e->cam != NULL) ? load_img(e, 27) : load_img(e, 28);
	(e->error != -1) ? error_gestion(e, 0, 0) : 0;
}

void			del_tab(t_envg *e)
{
	e->volet = (t_tab_valid){0, 0, 0, 1, 0};
	load_img(e, 4);
	load_img(e, 19);
	(e->i_lst > 15) ? load_img(e, 16) : 0;
	(e->e->nb_obj > e->page + 15) ? load_img(e, 17) : 0;
}
