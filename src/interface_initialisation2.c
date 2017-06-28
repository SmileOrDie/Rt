/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_initialisation2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:30:37 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 14:31:19 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

static void			init_pos_value2(t_envg *e)
{
	e->pos_value[23] = 8;
	e->pos_value[24] = 8;
	e->pos_value[25] = 8;
	e->pos_value[26] = 8;
	e->pos_value[30] = 13;
	e->pos_value[31] = 8;
}

void				init_pos_value(t_envg *e)
{
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
	init_pos_value2(e);
}
