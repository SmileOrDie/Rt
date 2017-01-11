/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:15:05 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:19:10 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

void			ft_error_var(t_vector *var, char *str, int f)
{
	if (f == 0)
	{
		if (!var)
			ft_error("a variable can't be NULL in : ", str);
		else if (var->x < 0 && var->y < 0 && var->z < 0)
			ft_error("x, y or z can't be negatif in : ", str);
	}
	if (f == 1)
	{
		if (var->x < 0 && var->x > 1 && var->y < 0 && var->y > 1 &&
			var->z < 0 && var->z > 1)
			ft_error("x, y or z can't be negatif or other 1 in : ", str);
	}
}
