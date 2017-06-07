/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_check_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/28 15:37:54 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

	// ft_strcpy(e->line[1], type_obj[(e->e->l_obj[obj].type - 1)]);
	// ft_strcpy(e->line[2], e->e->l_obj[obj].name);
	// ft_strcpy_nbr(e->line[3], e->e->l_obj[obj].pos.x);
	// ft_strcpy_nbr(e->line[4], e->e->l_obj[obj].pos.y);
	// ft_strcpy_nbr(e->line[5], e->e->l_obj[obj].pos.z);
	// ft_strcpy_nbr(e->line[6], e->e->l_obj[obj].dir.x);
	// ft_strcpy_nbr(e->line[7], e->e->l_obj[obj].dir.y);
	// ft_strcpy_nbr(e->line[8], e->e->l_obj[obj].dir.z);
	// ft_strcpy_nbr(e->line[9], e->e->l_obj[obj].color.r);
	// ft_strcpy_nbr(e->line[10], e->e->l_obj[obj].color.g);
	// ft_strcpy_nbr(e->line[11], e->e->l_obj[obj].color.b);

int 		sphere_check(char **def)			
{
	if (!def[2][0])
		return (1);
	else if (!def[3][0] || !def[4][0] || !def[5][0])
		return (2);
	else if (!def[9][0] || !def[10][0] || !def[11][0])
		return (4);
	else if (!def[12][0])
		return (5);
	return (-1);
}

int 		circle_check(char **def)			
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
	else if (!def[13][0])
		return (6);
	return (-1);
}

int 		plane_check(char **def)			
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

int 		cyl_check(char **def)			
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

int 		cone_check(char **def)			
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

int 		light_check(char **def)			
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
	static int (*obj_check[6])(char **def) = {sphere_check, plane_check, cyl_check, cone_check, light_check, circle_check};
	int obj;

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
	else
		return (0);
	return (obj_check[obj](def));
}