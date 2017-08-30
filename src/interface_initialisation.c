/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_initialisation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:34:10 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/16 19:30:39 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		init_pos_value(t_envg *e)
{
	int		i;

	i = 3;
	e->pos_value[0] = 12;
	e->pos_value[1] = 6;
	e->pos_value[2] = 6;
	while (i <= 15)
	{
		e->pos_value[i] = 8;
		i++;
	}
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
	e->pos_value[31] = 8;
}

static void	init_line_pos2(t_envg *e)
{
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
	e->line_pos[31] = (t_pos_i){91, 485};
}

void		init_line_pos(t_envg *e)
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
	init_line_pos2(e);
}
