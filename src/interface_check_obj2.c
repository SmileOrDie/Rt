/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_check_obj2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 17:37:57 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/16 19:29:28 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		check_new_obj(t_envg *e, t_obj *obj)
{
	(!ft_strcmp(e->line[1], "sphere")) ? obj->type = 1 : 0;
	(!ft_strcmp(e->line[1], "plane")) ? obj->type = 2 : 0;
	(!ft_strcmp(e->line[1], "cylinder")) ? obj->type = 3 : 0;
	(!ft_strcmp(e->line[1], "cone")) ? obj->type = 4 : 0;
	(!ft_strcmp(e->line[1], "circle")) ? obj->type = 5 : 0;
	(!ft_strcmp(e->line[1], "square")) ? obj->type = 6 : 0;
	(!ft_strcmp(e->line[1], "cube")) ? obj->type = 7 : 0;
	(!ft_strcmp(e->line[1], "cone_l")) || (obj->type == 4 &&
		ft_atof(e->line[12])
		!= 0) ? obj->type = 8 : 0;
	(!ft_strcmp(e->line[1], "cylinder_l")) || (obj->type == 3 &&
		ft_atof(e->line[31]) != 0) ? obj->type = 9 : 0;
}

int			sphere_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	else if (!def[12][0] || ft_atoi(def[12]) < 1)
		return (5);
	return (-1);
}

int			circ_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[6][0] || !def[7][0] || !def[8][0])
		return (3);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	else if (!def[12][0] || ft_atoi(def[12]) < 1)
		return (5);
	return (-1);
}

int			plane_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[6][0] || !def[7][0] || !def[8][0])
		return (3);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	return (-1);
}

int			cyl_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[6][0] || !def[7][0] || !def[8][0])
		return (3);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	else if (!def[12][0] || ft_atoi(def[12]) < 1)
		return (5);
	return (-1);
}
