/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init_mlx_envg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:49:39 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/12 19:10:36 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		init_envg2(t_envg *e, t_env *env)
{
	e->mlx->w = WI;
	e->mlx->h = HE;
	e->f_key = 0;
	e->font = 0;
	e->e = env;
	e->page = 0;
	e->i_lst = 0;
	e->shift = 1;
	e->pos = 0;
	e->run = 0;
	// e->e->anti_a = 1;
	e->filter = (t_filter){0, 0, 0, 0, 0, 0};
	e->error = -1;
}

void			init_envg(t_envg *e, t_env *env)
{
	int i;

	i = 0;
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return ;
	init_envg2(e, env);
	if (!(e->line = (char**)malloc(sizeof(char*) * LINE_SIZE + 1)))
		return ;
	while (i < LINE_SIZE)
	{
		if (!(e->line[i] = (char*)malloc(sizeof(char) * LINE_SIZE + 1)))
			return ;
		bzero(e->line[i++], LINE_SIZE);
	}
	init_line_pos(e);
	init_pos_value(e);
}

void			init_mlx(t_envg *e)
{
	e->img.img = NULL;
	if (!(e->mlx->mlx = mlx_init()))
		return ;
	else if (!(e->mlx->win =
		mlx_new_window(e->mlx->mlx, e->mlx->w, e->mlx->h,
			"Graphical interface by BIM")))
		return ;
	else if (!(e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->w,
		e->mlx->h)))
		return ;
	else if (!(e->mlx->data = mlx_get_data_addr(e->mlx->img, &(e->mlx->bpp),
		&(e->mlx->sizeline), &(e->mlx->endian))))
		return ;
	e->e->mlx->mlx = e->mlx->mlx;
}
