/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/21 16:49:39 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"


void		put_img5(t_envg *e)
{
	int img;
	char *str;
	t_parse_light *b;

	img = e->page + 3;
	e->i_lst = e->page;
	b = srch_light(e, e->i_lst);
	while (e->i_lst < img && b)
	{
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			40, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/deleted.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			60, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/Modify.xpm");
		str = ft_strdup(b->light.name);
		mlx_string_put(e->mlx->mlx, e->mlx->win,
			90, 400 + ((e->i_lst % 3)* 30), 0xFFFFFF, str);
		free(str);
		e->i_lst++;
		b = b->next;
	}
}
