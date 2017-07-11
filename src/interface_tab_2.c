/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_tab_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:49:25 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 17:49:36 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int					add_tab(t_envg *e)
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

void				info_tab(t_envg *e)
{
	int save;
	int i;

	load_img(e, 5);
	e->volet = (t_tab_valid){0, 0, 0, 0, 1};
	i = 1;
	save = e->pos;
	while (i <= 2)
	{
		e->pos = i;
		load_img(e, e->pos_value[i]);
		print_line(e, i + 40, 30);
		i++;
	}
	put_img6(e);
	e->pos = save;
}
