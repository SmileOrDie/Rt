/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_mouse3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:59:16 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 16:18:05 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void				interface_mouse_click2(int x, t_envg *e)
{
	if (x > 25 && x < 315)
		mousse_click_x(e, x);
	else
	{
		e->f_key = 0;
		e->i_lst = 0;
		e->mod = 0;
	}
}

void				interface_mouse_click3(t_envg *e)
{
	init_id(e->e);
	if (e->run == 1)
	{
		pthread_join(e->thread, NULL);
		e->thread = NULL;
		ft_exit(e);
	}
	e->run = 1;
	init_mlx1(e);
	event_touch(e);
	ft_creat_lst_obj(e->e);
	ft_get_image_texture(e->e);
	pthread_create(&e->thread, NULL, ft_launch, e->e);
}

int					interface_mouse_click(int button, int x, int y, t_envg *e)
{
	if (button == 1)
	{
		if (e->error != -1)
			return (error_gestion(e, x, y));
		else if (y > 125 && y < 150)
			interface_mouse_click2(x, e);
		else if (y > 830 && y < 900 && e->volet.home == 1 && (e->e->nb_obj > 0 \
			&& e->e->cam != NULL))
			interface_mouse_click3(e);
		e->pos = select_pos(e, x, y);
		if (e->volet.add == 1 && (((e->pos > 0 && e->pos <= 15) || \
		e->pos == 31) || e->pos == -1))
			e->pos = add_tab(e);
		else if (e->volet.conf == 1 && ((((e->pos > 0 && e->pos <= 15) || \
		e->pos == 31) ||
			(e->pos >= 19 && e->pos <= 26)) || e->pos == -1))
		{
			e->i_lst = 0;
			e->pos = conf_tab(e);
		}
		else if (e->volet.info == 1 && e->pos > 40 && e->pos < 43)
			info_tab(e);
		volet_target(e);
	}
	return (1);
}
