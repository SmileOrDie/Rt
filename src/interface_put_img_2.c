/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/05 15:54:41 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"


void		put_img5(t_envg *e)
{
	int img;
	char *str;

	img = e->page + 3;
	e->i_lst = e->page;
	while (e->i_lst < img && e->i_lst < e->e->nb_light)
	{
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			40, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/deleted.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			60, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/Modify.xpm");
		str = ft_strdup(e->e->light[e->i_lst].name);
		mlx_string_put(e->mlx->mlx, e->mlx->win,
			90, 400 + ((e->i_lst % 3)* 30), 0xFFFFFF, str);
		free(str);
		e->i_lst++;
	}
}