/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:39:22 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/24 11:30:17 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color			*get_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color		*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		ft_error(MALLOC, "=> (put_pixel.c)");
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

// void			put_pixel(int x, int y, t_env *e)
// {
// 	char		*pos;

// 	pos = e->mlx->data + (y * e->mlx->sizeline + (e->mlx->bpp / 8) * x);
// 	// // pos = (y * e->mlx->sizeline + (e->mlx->bpp / 8) * x);
// 	// if (e->mlx->endian == 1)
// 	// {
// 		*pos = (unsigned char)e->r;
// 		*(pos + 1) = (unsigned char)e->g;
// 		*(pos + 2) = (unsigned char)e->b;
// 		// e->mlx->data[pos] = (unsigned char)e->r;
// 		// e->mlx->data[pos + 1] = (unsigned char)e->g;
// 		// e->mlx->data[pos + 2] = (unsigned char)e->b;
// 	// }
// 	// else
// 	// {
// 	// 	e->mlx->data[pos] = (unsigned char)e->b;
// 	// 	e->mlx->data[pos + 1] = (unsigned char)e->g;
// 	// 	e->mlx->data[pos + 2] = (unsigned char)e->r;
// 	// }
// }

void			put_pixel(int x, int y, t_env *e)
{
	unsigned char		*pos;

	pos = e->mlx->data + y * e->mlx->sizeline + e->mlx->bpp / 8 * x;
	*pos = (unsigned char)e->b;
	*(pos + 1) = (unsigned char)e->g;
	*(pos + 2) = (unsigned char)e->r;
}
