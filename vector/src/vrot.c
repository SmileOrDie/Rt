/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vrot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:36:23 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/06 17:54:26 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	vrot(t_vector u, double angle, t_vector point)
{
	t_vector	r;
	double		c;
	double		s;
	double		mat[3][3];

	c = cos(angle / 360 * 2 * M_PI);
	s = sin(angle / 360 * 2 * M_PI);
	vnorm(&u);
	mat[0][0] = u.x * u.x * (1 - c) + c;
	mat[0][1] = u.x * u.y * (1 - c) + u.z * s;
	mat[0][2] = u.x * u.z * (1 - c) - u.y * s;
	mat[1][0] = u.y * u.x * (1 - c) - u.z * s;
	mat[1][1] = u.y * u.y * (1 - c) + c;
	mat[1][2] = u.y * u.z * (1 - c) + u.x * s;
	mat[2][0] = u.z * u.x * (1 - c) + u.y * s;
	mat[2][1] = u.z * u.y * (1 - c) - u.x * s;
	mat[2][2] = u.z * u.z * (1 - c) + c;
	r.x = mat[0][0] * point.x + mat[1][0] * point.y + mat[2][0] * point.z;
	r.y = mat[0][1] * point.x + mat[1][1] * point.y + mat[2][1] * point.z;
	r.z = mat[0][2] * point.x + mat[1][2] * point.y + mat[2][2] * point.z;
	return (r);
}
