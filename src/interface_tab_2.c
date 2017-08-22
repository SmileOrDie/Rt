/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_tab_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 19:15:42 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/22 17:49:14 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			info_tab(t_envg *e)
{
	int			save;
	int			i;

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

static void		conf_tab2(t_envg *e, int i)
{
	int				nb;
	t_parse_light	*b;

	b = e->parse_light;
	nb = 0;
	while (b)
	{
		nb++;
		b = b->next;
	}
	while (i < 27)
	{
		e->pos = i;
		load_img(e, e->pos_value[i]);
		print_line(e, i, 3);
		i++;
	}
	put_img7(e);
	put_img8(e);
	load_img(e, 21);
	load_img(e, 24);
	(e->i_lst > 3) ? load_img(e, 22) : 0;
	(nb > e->page + 3) ? load_img(e, 23) : 0;
}

void			conf_tab3(t_envg *e, int i)
{
	if (e->mod == 1)
	{
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
	}
	else
		conf_tab2(e, 18);
}
