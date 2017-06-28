/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_check_obj2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:23:51 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 13:22:34 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

int			sphere_check(char **def)
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

int			circle_check(char **def)
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
