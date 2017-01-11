/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:53:30 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/19 17:39:19 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	return_quad(double *t, double x)
{
	*t = x;
	return (1);
}

int			solve_quad(double a, double b, double c, double *t)
{
	t_quad	v;

	v.delta = b * b - 4 * a * c;
	if (v.delta > 0)
	{
		v.sqrt_delta = sqrt(v.delta);
		v.q = -.5 * (b + v.sqrt_delta);
		v.x0 = v.q / a;
		v.x1 = (v.q + v.sqrt_delta) / a;
		if (*t > v.x0 && v.x0 >= 0.1 && (v.x1 <= 0.1 || v.x1 >= v.x0))
			return (return_quad(t, v.x0));
		if (*t > v.x1 && v.x1 >= 0.1)
			return (return_quad(t, v.x1));
	}
	else if (v.delta == 0)
	{
		*t = 0;
		return (1);
	}
	return (0);
}
