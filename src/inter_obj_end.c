/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:18 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 13:05:42 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

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
	t_norme5	n;

	n.d = vpscal(p.dir, vsub(p.pos, o));
	n.nd = vpscal(p.dir, dir);
	n.te = n.d / n.nd;
	if (n.nd < 0.00001 && n.nd > -0.00001)
		return (-1);
	if (n.te > 0)
	{
		n.cross = (p.dir.x == 1) ? (t_vector){0, 1, 0, 0} : \
		(t_vector){1, 0, 0, 0};
		n.p_hit = vadd(o, vmult_dbl(dir, n.te));
		n.u = vsub(n.p_hit, p.pos);
		n.cross = vcross(p.dir, n.cross);
		n.cross = vrot(p.dir, p.angle, n.cross);
		if (vpscal(n.cross, n.u) < p.radius / 2 && vpscal(n.cross, n.u) > \
		-p.radius / 2)
		{
			n.cross = vcross(n.cross, p.dir);
			if (vpscal(n.cross, n.u) < p.radius / 2 && vpscal(n.cross, n.u) > \
			-p.radius / 2)
				return (n.te);
		}
	}
	return (-1.0);
}
