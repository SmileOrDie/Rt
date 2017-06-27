/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_and_apply_filtre.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:25:53 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/27 19:00:11 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			*lecture_img_for_blur(t_env *e, int x, int y, int i)
{
	int		*tab;
	int		compt;
	int		s;

	s = x;
	compt = 0;
	if (!(tab = (int *)malloc(sizeof(int) * 101)))
		ft_error(MALLOC, "lecture_img_to_blur");
	while (i < 100 && y < e->mlx->h)
	{
		tab[i] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 2];
		tab[i + 1] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
			((e->mlx->bpp / 8) * x) + 1];
		tab[i + 2] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
			((e->mlx->bpp / 8) * x)];
		tab[i + 3] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
			((e->mlx->bpp / 8) * x++) + 3];
		i += 4;
		if (x > e->mlx->w / e->anti_a || compt++ == 5)
		{
			y++;
			x = s;
			compt = 0;
		}
	}
	return (tab);
}

int			apply_color_pix_for_blur(t_env *e, int rgb[5], int x, int y)
{
	if (y >= e->mlx->h || x >= e->mlx->w)
		return (0);
	rgb[0] = rgb[0] / 256;
	rgb[1] = rgb[1] / 256;
	rgb[2] = rgb[2] / 256;
	rgb[3] = rgb[3] / 256;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	if (rgb[3] > 255)
		rgb[3] = 255;
	e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 2] = (unsigned char)rgb[0];
	e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 1] = (unsigned char)rgb[1];
	e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x)] = (unsigned char)rgb[2];
	e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 3] = (unsigned char)rgb[3];
	return (0);
}

void		lecture_img(t_env *e, int (rgb)[5], int x, int y)
{
	rgb[0] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x) + 2];
	rgb[1] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x) + 1];
	rgb[2] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x)];
}

void		apply_color_pix(t_env *e, int rgb[5], int x, int y)
{
	e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x) + 2] = (unsigned char)rgb[0];
	e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x) + 1] = (unsigned char)rgb[1];
	e->mlx->data[(y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * x)] = (unsigned char)rgb[2];
}
