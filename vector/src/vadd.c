/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vadd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:05:18 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:18:41 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	*vadd(t_vector *a, t_vector *b)
{
	t_vector *c;

	if (!(c = (t_vector *)malloc(sizeof(t_vector))))
		ft_error(MALLOC, "t_vector *vadd(t_vector *a, t_vector *b);");
	else if (!a || !b)
		ft_error(ARG_N, "t_vector *vadd(t_vector *a, t_vector *b);");
	else
	{
		c->x = a->x + b->x;
		c->y = a->y + b->y;
		c->z = a->z + b->z;
		c->p = 1;
	}
	return (c);
}

t_vector	vadd2(t_vector *a, t_vector *b)
{
	t_vector c;

	c.x = a->x + b->x;
	c.y = a->y + b->y;
	c.z = a->z + b->z;
	c.p = 1;
	return (c);
}
