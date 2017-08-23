/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:25:48 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/23 15:27:08 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void	ft_rgb(char *data, int pos, int rgb)
{
	data[pos] = rgb == 0 || rgb == 1 ? 0 : data[pos];
	data[pos + 1] = rgb == 1 || rgb == 2 ? 0 : data[pos + 1];
	data[pos + 2] = rgb == 0 || rgb == 2 ? 0 : data[pos + 2];
}

static void	filter_rgb(t_env *e, int x, int y, int rgb)
{
	int		pos;
	t_pos	size;

	size.h = e->win.h / e->anti_a;
	size.w = e->win.w / e->anti_a;
	pos = 0;
	while (y < size.h)
	{
		pos = (y * size.w * 4) + 4 * x;
		ft_rgb(e->mlx.data, pos, rgb);
		x++;
		if (x >= size.w && ((y++) || 1))
			x = 0;
	}
}

void		filter_red(t_env *e, int x, int y)
{
	filter_rgb(e, x, y, 1);
}

void		filter_blue(t_env *e, int x, int y)
{
	filter_rgb(e, x, y, 2);
}

void		filter_green(t_env *e, int x, int y)
{
	filter_rgb(e, x, y, 0);
}
