/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:18 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/10 16:25:21 by pde-maul         ###   ########.fr       */
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
	double		d;
	double		nd;
	double		te;
	t_vector	p_hit;
	t_vector	u;
	t_vector	v;
	t_vector	cross;

	d = vpscal(p.dir, vsub(p.pos, o));
	nd = vpscal(p.dir, dir);
	te = d / nd;
	if (nd < 0.00001 && nd > -0.00001)
		return (-1);
	if (te > 0)
	{
		cross = (t_vector){1, 1, 1, 0};
		p_hit = vadd(o, vmult_dbl(dir, te));
		u = vsub(p_hit, p.pos);
		vnorm(&cross);
		v = vcross(cross, p.dir);
		cross = vrot(p.dir, p.angle, cross);
		// cross = vmult_dbl(cross, p.radius / 2 * p.radius / 2);
		if (vpscal(cross, u) < p.radius / 2 && vpscal(cross, u) > -p.radius / 2)
			return (te);
		return (0);
	}
	return (-1.0);
}
