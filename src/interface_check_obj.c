/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_check_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/28 13:21:15 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

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
	else if (!def[13][0])
		return (6);
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
	else if (!def[12][0])
		return (5);
	return (-1);
}

int			cone_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[6][0] || !def[7][0] || !def[8][0])
		return (3);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	else if (!def[13][0])
		return (6);
	return (-1);
}

int			light_check(char **def)
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	return (-1);
}

int			check_var_obj(char **def)
{
	static int		(*obj_check[6])(char **def) = {sphere_check, plane_check,
					cyl_check, cone_check, light_check, circle_check};
	int				obj;

	if (!ft_strcmp("sphere", def[1]))
		obj = 0;
	else if (!ft_strcmp("plane", def[1]))
		obj = 1;
	else if (!ft_strcmp("cylinder", def[1]))
		obj = 2;
	else if (!ft_strcmp("cone", def[1]))
		obj = 3;
	else if (!ft_strcmp("light", def[1]))
		obj = 4;
	else if (!ft_strcmp("circle", def[1]))
		obj = 5;
	else if (!ft_strcmp("square", def[1]))
		obj = 1;
	else if (!ft_strcmp("cube", def[1]))
		obj = 1;
	else
		return (0);
	return (obj_check[obj](def));
}
