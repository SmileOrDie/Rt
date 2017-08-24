/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_selection_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:59:14 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 13:54:16 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		select_info_2(t_envg *e, int i)
{
	(i == 1) ? save_scene(e, NULL, -1) : bmp_save_img(e);
	home_tab(e);
}

int				select_info(t_envg *e, int x, int y)
{
	int i;

	i = 0;
	while (++i <= 2)
		if (x > e->line_pos[i].w && x < e->line_pos[i].w + 317 &&
			y > e->line_pos[i].h && y < e->line_pos[i].h + 30)
			return (i + 40);
	if (e->line[41][0] && x > 290 && x < 390 && y > 245 && y < 265)
		add_new_texture(e);
	else if (e->line[42][0] && x > 290 && x < 390 && y > 295 && y < 315)
		free_env_parse(e);
	else if (e->nb_obj > 0 && e->cam.set && x > 40 && x < 135 &&
		y > 330 && y < 355)
		select_info_2(e, 1);
	else if (e->e && e->e->mlx.img != NULL && x > 145 && x < 245 && y > 335
	&& y < 355)
		select_info_2(e, 0);
	else
		info_tab(e);
	return (-1);
}
