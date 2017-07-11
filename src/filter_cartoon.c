/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cartoon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:48:33 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/11 15:40:36 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

static int		*lecture_img_for_cartoon(t_env *e, int x, int y, int i)
{
	t_norme17	n;

	n.s = x;
	n.tab = NULL;
	n.compt = 0;
	if (!(n.tab = (int *)malloc(sizeof(int) * 37)))
		ft_error(MALLOC, "lecture_img_to_blur");
	while (i < 37 && y < e->mlx->h)
	{
		n.tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 2];
		n.tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x) + 1];
		n.tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x)];
		n.tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * x++) + 3];
		if (x > e->mlx->w || n.compt++ == 3)
		{
			y++;
			x = n.s;
			n.compt = 0;
		}
	}
	return (n.tab);
}

static int		apply_color_pix_for_cartoon(t_env *e, int rgb[5], int x, int y)
{
	if (y >= e->mlx->h || x >= e->mlx->w)
		return (0);
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

void			filter_cartoon(t_env *e, int x, int y)
{
	int		*tab;
	int		rgb[5];

	y = 1;
	x = 2;
	tab = NULL;
	while (y <= e->mlx->h - 1)
	{
		tab = lecture_img_for_cartoon(e, x, y, 0);
		rgb[0] = tab[0] * 11 + tab[4] * 23 + tab[8] * 53 + tab[12] * 61 + \
	tab[16] * 74 + tab[20] * 81 + tab[24] * 20 + tab[28] * 34 + tab[32] * 56;
		rgb[1] = tab[0] * 11 + tab[4] * 23 + tab[8] * 53 + tab[12] * 61 + \
	tab[16] * 74 + tab[20] * 81 + tab[24] * 20 + tab[28] * 34 + tab[32] * 56;
		rgb[2] = tab[0] * 11 + tab[4] * 23 + tab[8] * 53 + tab[12] * 61 + \
	tab[16] * 74 + tab[20] * 81 + tab[24] * 20 + tab[28] * 34 + tab[32] * 56;
		rgb[3] = tab[0] * 11 + tab[4] * 23 + tab[8] * 53 + tab[12] * 61 + \
	tab[16] * 74 + tab[20] * 81 + tab[24] * 20 + tab[28] * 34 + tab[32] * 56;
		apply_color_pix_for_cartoon(e, rgb, x, y);
		x++;
		if (x > e->mlx->w)
		{
			y++;
			x = 0;
		}
	}
}
