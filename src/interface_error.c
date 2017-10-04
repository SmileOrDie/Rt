/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:02:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 12:27:21 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void	ft_error_graph(t_envg *e, char *error_val)
{
	char *error;

	load_img(e, 26);
	if (e->error < 7)
		error = (e->error == 0 || e->error == 1) ?
		ft_strjoin("Error", error_val) : ft_strjoin(e->line[2], error_val);
	else
		error = ft_strjoin("text.", error_val);
	mlx_string_put(e->mlx.mlx, e->mlx.win, (WI / 2) -
		(ft_strlen(error) * 5), e->line_pos[27].h + 40, 0x000000, error);
	free(error);
}

int			error_gestion(t_envg *e, int x, int y)
{
	char *tab_error[25];

	tab_error[0] = " : Object inquiry";
	tab_error[1] = " : Object name";
	tab_error[2] = " : Position information";
	tab_error[3] = " : Direction information";
	tab_error[4] = " : Color information";
	tab_error[5] = " : Radius/angle information";
	tab_error[6] = " : ";
	tab_error[7] = " : Texture doesn't exist";
	tab_error[8] = " : Type not supported";
	tab_error[9] = " : Texture already exist";
	tab_error[10] = " : ";
	e->f_key = 0;
	if (x > (WI / 2 - 35) && x < (WI / 2 + 35) &&
		y > ((HE / 2 + 30) - 15) && y < ((HE / 2 + 30) + 15))
	{
		e->i_lst = 0;
		e->page = 0;
		e->error = -1;
		home_tab(e);
	}
	else
		ft_error_graph(e, tab_error[e->error]);
	return (1);
}
