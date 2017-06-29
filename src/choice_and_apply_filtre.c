/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_and_apply_filtre.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:25:53 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/29 12:42:13 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

int			*lecture_img_for_blur2(t_env *e, t_norme *n, int *tab)
{
	tab[n->i] = (unsigned char)e->mlx->data[(n->y * e->mlx->sizeline) + \
	((e->mlx->bpp / 8) * n->x) + 2];
	tab[n->i + 1] = (unsigned char)e->mlx->data[(n->y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * n->x) + 1];
	tab[n->i + 2] = (unsigned char)e->mlx->data[(n->y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * n->x)];
	tab[n->i + 3] = (unsigned char)e->mlx->data[(n->y * e->mlx->sizeline) + \
		((e->mlx->bpp / 8) * n->x++) + 3];
	return (tab);
}

int			*lecture_img_for_blur(t_env *e, int x, int y, int i)
{
	int		*tab;
	int		compt;
	int		s;
	t_norme	n;

	s = x;
	n.x = x;
	n.y = y;
	n.i = i;
	n.s = s;
	compt = 0;
	if (!(tab = (int *)malloc(sizeof(int) * 101)))
		ft_error(MALLOC, "lecture_img_to_blur");
	while (n.i < 100 && n.y < e->mlx->h)
	{
		lecture_img_for_blur2(e, &n, tab);
		n.i += 4;
		if (n.x > e->mlx->w / e->anti_a || compt++ == 5)
		{
			n.y++;
			n.x = n.s;
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
