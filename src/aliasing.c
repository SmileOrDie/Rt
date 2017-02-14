/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliasing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <magouin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:26:13 by magouin           #+#    #+#             */
/*   Updated: 2017/02/02 18:03:56 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_moyenne(t_env *e, int x, int y, int c)
{
	y *= 4;
	x *= 4;
	e->mlx->data4[x + c + e->mlx->w * y / 4] = (int)(
		(int)(e->mlx->data[x * 4 + c + y * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + y * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c +(y + 1) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 1) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + y * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + y * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 1) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 1) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c +(y + 2) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 2) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c +(y + 3) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 3) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 2) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 2) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c +(y + 3) * 4 * e->mlx->w]) +
		(int)(e->mlx->data[x * 4 + c + (y + 3) * 4 * e->mlx->w])) / 16;
}

void	*ft_aliasing(void *env)
{
	int x;
	int y;
	t_env *e;

	e = (t_env *)env;
	x = 0;
	// while (y < e->mlx->h / 4)
	// {
	// 	x = 0;
	// 	while (x < e->mlx->w / 4)
	// 	{
	// 		ft_moyenne(e, x, y, 0);
	// 		ft_moyenne(e, x, y, 1);
	// 		ft_moyenne(e, x, y, 2);
	// 		x++;
	// 	}
	// 	y++;
	// }
	while (x < e->l.x_end / 4)
	{	
		y = e->l.y_start;
		while (y < e->l.y_end / 4)
		{
			ft_moyenne(e, x, y, 0);
			ft_moyenne(e, x, y, 1);
			ft_moyenne(e, x, y, 2);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}
