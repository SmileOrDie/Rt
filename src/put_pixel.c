/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:39:22 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/19 17:49:08 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color			*get_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color		*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		ft_error(MALLOC, " => (put_pixel.c)");
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

void			put_pixel(int x, int y, t_env *e)
{
	char		*pos;

	pos = e->mlx->data + y * e->mlx->sizeline + e->mlx->bpp / 8 * x;
	*pos = (unsigned char)e->b;
	*(pos + 1) = (unsigned char)e->g;
	*(pos + 2) = (unsigned char)e->r;
}
