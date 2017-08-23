/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:55:01 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/23 16:04:27 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void		apply_blur_to_r(int *rgb, int i, int *tab)
{
	rgb[0] = tab[i - 50] * 1 + tab[i - 46] * 4 + tab[i - 42] * 6
		+ tab[i - 38] * 4 + tab[i - 34] * 1
		+ tab[i - 30] * 4 + tab[i - 26] * 16 + tab[i - 22] * 24
		+ tab[i - 18] * 16 + tab[i - 14] * 4
		+ tab[i - 10] * 6 + tab[i - 6] * 24 + tab[i - 2] * 36
		+ tab[i + 2] * 24 + tab[i + 6] * 26
		+ tab[i + 10] * 4 + tab[i + 14] * 16 + tab[i + 18] * 24
		+ tab[i + 22] * 16 + tab[i + 26] * 4
		+ tab[i + 30] * 1 + tab[i + 34] * 4 + tab[i + 38] * 6
		+ tab[i + 42] * 4 + tab[i + 46] * 1;
}

static void		apply_blur_to_g(int *rgb, int i, int *tab)
{
	rgb[1] = tab[i - 50] * 1 + tab[i - 46] * 4 + tab[i - 42] * 6
		+ tab[i - 38] * 4 + tab[i - 34] * 1
		+ tab[i - 30] * 4 + tab[i - 26] * 16 + tab[i - 22] * 24
		+ tab[i - 18] * 16 + tab[i - 14] * 4
		+ tab[i - 10] * 6 + tab[i - 6] * 24 + tab[i - 2] * 36
		+ tab[i + 2] * 24 + tab[i + 6] * 26
		+ tab[i + 10] * 4 + tab[i + 14] * 16 + tab[i + 18] * 24
		+ tab[i + 22] * 16 + tab[i + 26] * 4
		+ tab[i + 30] * 1 + tab[i + 34] * 4 + tab[i + 38] * 6
		+ tab[i + 42] * 4 + tab[i + 46] * 1;
}

static void		apply_blur_to_b(int *rgb, int i, int *tab)
{
	rgb[2] = tab[i - 50] * 1 + tab[i - 46] * 4 + tab[i - 42] * 6
		+ tab[i - 38] * 4 + tab[i - 34] * 1
		+ tab[i - 30] * 4 + tab[i - 26] * 16 + tab[i - 22] * 24
		+ tab[i - 18] * 16 + tab[i - 14] * 4
		+ tab[i - 10] * 6 + tab[i - 6] * 24 + tab[i - 2] * 36
		+ tab[i + 2] * 24 + tab[i + 6] * 26
		+ tab[i + 10] * 4 + tab[i + 14] * 16 + tab[i + 18] * 24
		+ tab[i + 22] * 16 + tab[i + 26] * 4
		+ tab[i + 30] * 1 + tab[i + 34] * 4 + tab[i + 38] * 6
		+ tab[i + 42] * 4 + tab[i + 46] * 1;
}

static void		apply_blur_to_t(int *rgb, int i, int *tab)
{
	rgb[3] = tab[i - 50] * 1 + tab[i - 46] * 4 + tab[i - 42] * 6
		+ tab[i - 38] * 4 + tab[i - 34] * 1
		+ tab[i - 30] * 4 + tab[i - 26] * 16 + tab[i - 22] * 24
		+ tab[i - 18] * 16 + tab[i - 14] * 4
		+ tab[i - 10] * 6 + tab[i - 6] * 24 + tab[i - 2] * 36
		+ tab[i + 2] * 24 + tab[i + 6] * 26
		+ tab[i + 10] * 4 + tab[i + 14] * 16 + tab[i + 18] * 24
		+ tab[i + 22] * 16 + tab[i + 26] * 4
		+ tab[i + 30] * 1 + tab[i + 34] * 4 + tab[i + 38] * 6
		+ tab[i + 42] * 4 + tab[i + 46] * 1;
}

void			filter_blur(t_env *e, int x, int y)
{
	int *tab;
	int rgb[5];

	y = 0;
	x = 0;
	tab = NULL;
	while (y < e->win.h / e->anti_a)
	{
		if (!(tab = lecture_img_for_blur(e, x, y, 0)))
			ft_error("error filter", "filter blur");
		apply_blur_to_r(rgb, 50, tab);
		apply_blur_to_g(rgb, 51, tab);
		apply_blur_to_b(rgb, 52, tab);
		apply_blur_to_t(rgb, 53, tab);
		free(tab);
		if (apply_color_pix_for_blur(e, rgb, x, y) == -1)
			break ;
		x++;
		if (x >= e->win.w / e->anti_a && ((y++) || 1))
			x = 0;
	}
}
