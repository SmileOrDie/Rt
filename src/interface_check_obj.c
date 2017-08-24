/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_check_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/12 18:07:24 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int			co_check(char **def)
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

int			co_l_check(char **def)
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

int			cyl_l_check(char **def)
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
	static int (*obj_check[8])(char **def) = {sphere_check, plane_check,
		cyl_check, co_check, light_check, circ_check, co_l_check, cyl_l_check};

	if (!ft_strcmp("sphere", def[1]))
		return (obj_check[0](def));
	else if (!ft_strcmp("plane", def[1]))
		return (obj_check[1](def));
	else if (!ft_strcmp("cylinder", def[1]))
		return (obj_check[2](def));
	else if (!ft_strcmp("cone", def[1]))
		return (obj_check[3](def));
	else if (!ft_strcmp("light", def[1]))
		return (obj_check[4](def));
	else if (!ft_strcmp("circle", def[1]))
		return (obj_check[5](def));
	else if (!ft_strcmp("square", def[1]))
		return (obj_check[7](def));
	else if (!ft_strcmp("cube", def[1]))
		return (obj_check[7](def));
	else if (!ft_strcmp("cone_l", def[1]))
		return (obj_check[6](def));
	else if (!ft_strcmp("cylinder_l", def[1]))
		return (obj_check[7](def));
	return (0);
}
