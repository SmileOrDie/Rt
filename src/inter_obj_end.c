/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:18 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/12 17:36:31 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double			inter_circle(t_obj p, t_vector o, t_vector dir)
{
	double		d;
	double		nd;
	double		te;
	t_vector	qe;

	qe = vsub(p.pos, o);
	d = vpscal(p.dir, qe);
	nd = vpscal(p.dir, dir);
	te = d / nd;
	if (nd < 0.00001 && nd > -0.00001)
		return (-1);
	if (te > 0)
	{
		if (vsize(vsub(vadd(vmult_dbl(dir, te), o), p.pos)) > p.radius)
			return (-1);
		return (te);
	}
	return (-1.0);
}

double			inter_square(t_obj p, t_vector o, t_vector dir)
{
	double		t[3];
	t_vector	u;
	t_vector	c;

	t[0] = vpscal(p.dir, vsub(p.pos, o));
	t[1] = vpscal(p.dir, dir);
	if (t[1] < 0.00001 && t[1] > -0.00001)
		return (-1);
	t[2] = t[0] / t[1];
	if (t[2] > 0)
	{
		c = (p.dir.x == 1) ? (t_vector){0, 1, 0, 0} : (t_vector){1, 0, 0, 0};
		u = vsub(vadd(o, vmult_dbl(dir, t[2])), p.pos);
		c = vrot(p.dir, p.angle, vcross(p.dir, c));
		vnorm(&c);
		vnorm(&p.point);
		c = (p.point.x != 0 || p.point.y != 0 || p.point.z != 0) ? p.point : c;
		if (vpscal(c, u) < p.radius / 2 && vpscal(c, u) > -p.radius / 2)
		{
			c = vcross(c, p.dir);
			return (vpscal(c, u) < p.radius / 2 && vpscal(c, u) > -p.
				radius / 2 ? t[2] : -1.0);
		}
	}
	return (-1.0);
}
