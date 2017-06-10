/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_initialisation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:34:10 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/21 16:09:51 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		init_pos_value(t_envg *e)
{
	// if (!(e->pos_value = (int *)malloc(sizeof(int) * 31)))
	// 	return ;
	e->pos_value[0] = 12;
	e->pos_value[1] = 6;
	e->pos_value[2] = 6;
	e->pos_value[3] = 8;
	e->pos_value[4] = 8;
	e->pos_value[5] = 8;
	e->pos_value[6] = 8;
	e->pos_value[7] = 8;
	e->pos_value[8] = 8;
	e->pos_value[9] = 8;
	e->pos_value[10] = 8;
	e->pos_value[11] = 8;
	e->pos_value[12] = 8;
	e->pos_value[13] = 8;
	e->pos_value[14] = 8;
	e->pos_value[15] = 8;
	e->pos_value[16] = 14;
	e->pos_value[18] = 18;
	e->pos_value[19] = 8;
	e->pos_value[20] = 8;
	e->pos_value[21] = 8;
	e->pos_value[22] = 8;
	e->pos_value[23] = 8;
	e->pos_value[24] = 8;
	e->pos_value[25] = 8;
	e->pos_value[26] = 8;
	e->pos_value[30] = 13;
}

static void		init_line_pos(t_envg *e)
{
	e->line_pos[0] = (t_pos_i){40, 195};
	e->line_pos[1] = (t_pos_i){37, 210};
	e->line_pos[2] = (t_pos_i){37, 265};
	e->line_pos[3] = (t_pos_i){37, 320};
	e->line_pos[4] = (t_pos_i){91, 320};
	e->line_pos[5] = (t_pos_i){144, 320};
	e->line_pos[6] = (t_pos_i){37, 375};
	e->line_pos[7] = (t_pos_i){91, 375};
	e->line_pos[8] = (t_pos_i){144, 375};
	e->line_pos[9] = (t_pos_i){37, 430};
	e->line_pos[10] = (t_pos_i){91, 430};
	e->line_pos[11] = (t_pos_i){144, 430};
	e->line_pos[12] = (t_pos_i){37, 485};
	e->line_pos[13] = (t_pos_i){37, 540};
	e->line_pos[14] = (t_pos_i){91, 540};
	e->line_pos[15] = (t_pos_i){144, 540};
	e->line_pos[16] = (t_pos_i){50, HE - 200};
	e->line_pos[17] = (t_pos_i){250, HE - 200};
	e->line_pos[18] = (t_pos_i){40, 200};
	e->line_pos[19] = (t_pos_i){37, 210};
	e->line_pos[20] = (t_pos_i){91, 210};
	e->line_pos[21] = (t_pos_i){144, 210};
	e->line_pos[22] = (t_pos_i){37, 265};
	e->line_pos[23] = (t_pos_i){91, 265};
	e->line_pos[24] = (t_pos_i){144, 265};
	e->line_pos[25] = (t_pos_i){37, 320};
	e->line_pos[26] = (t_pos_i){91, 320};
	e->line_pos[27] = (t_pos_i){WI / 2 - 150, HE / 2 - 50};
	e->line_pos[28] = (t_pos_i){WI / 2 - 62, 830};
	e->line_pos[29] = (t_pos_i){WI / 2 - 62, 830};
	e->line_pos[30] = (t_pos_i){250, HE - 200};
}

void			init_envg(t_envg *e, t_env *env)
{
	int i;

	i = 0;
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return ;
	e->mlx->w = WI;
	e->mlx->h = HE;
	e->f_key = 0;
	e->font = 0;
	e->e = env;
	e->page = 0;
	e->i_lst = 0;
	e->shift = 1;
	e->run = 0;
	e->filter = (t_filter){0, 0, 0, 0, 0, 0};
	e->error = -1;
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

void				init_mlx(t_envg *e)
{
	e->img.img = NULL;
	if (!(e->mlx->mlx = mlx_init()))
		return ;
	else if (!(e->mlx->win =
		mlx_new_window(e->mlx->mlx, e->mlx->w, e->mlx->h,
			"Graphical interface by BIM")))
		return ;
	else if (!( e->mlx->img = mlx_new_image(e->mlx->mlx, e->mlx->w,
		e->mlx->h)))
		return ;
	else if (!(e->mlx->data = mlx_get_data_addr(e->mlx->img, &(e->mlx->bpp),
		&(e->mlx->sizeline), &(e->mlx->endian))))
		return ;
	e->e->mlx->mlx = e->mlx->mlx;
}
