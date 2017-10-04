/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/12 18:00:59 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

double			solve_quad(double a, double b, double c)
{
	double			delta;
	double			sqrt_delta;
	double			x0;
	double			x1;
	double			q;

	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		sqrt_delta = sqrt(delta);
		q = -0.5 * (b + sqrt_delta);
		x0 = q / a;
		x1 = (q + sqrt_delta) / a;
		if (x0 > 0.00001 && (x1 < 0.00001 || x1 >= x0))
			return (x0);
		if (x1 > 0.00001)
			return (x1);
		return (-1);
	}
	return (-1);
}

double			inter_sphere(t_obj sp, t_vector o, t_vector dir)
{
	t_vector	dist_s;
	double		ab[2];
	double		d;
	double		t0;
	double		t1;

	dist_s = vsub(sp.pos, o);
	ab[1] = vpscal(dir, dist_s);
	d = ab[1] * ab[1] - vpscal(dist_s, dist_s) + sp.radius * sp.radius;
	if (d <= 0.00001)
		return (-1);
	ab[0] = sqrt(d);
	t0 = ab[1] - ab[0];
	t1 = ab[1] + ab[0];
	if (t0 > 0.00001 && (t1 < 0.00001 || t1 >= t0))
		return (t0);
	else if (t1 > 0.00001)
		return (t1);
	return (-1.0);
}

double			inter_plane(t_obj p, t_vector o, t_vector dir)
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
		return (te);
	return (-1.0);
}

double			inter_cylinder(t_obj cyl, t_vector o, t_vector dir)
{
	double		t[3];
	double		abc[3];
	t_vector	dp;
	t_vector	tmp;
	t_vector	tmp2;

	dp = vsub(o, cyl.pos);
	t[0] = vpscal(dir, cyl.dir);
	abc[0] = dir.x - t[0] * cyl.dir.x;
	abc[1] = dir.y - t[0] * cyl.dir.y;
	abc[2] = dir.z - t[0] * cyl.dir.z;
	tmp = new_v(abc[0], abc[1], abc[2]);
	t[1] = vpscal(dp, cyl.dir);
	abc[0] = dp.x - t[1] * cyl.dir.x;
	abc[1] = dp.y - t[1] * cyl.dir.y;
	abc[2] = dp.z - t[1] * cyl.dir.z;
	tmp2 = new_v(abc[0], abc[1], abc[2]);
	t[2] = solve_quad(vpscal(tmp, tmp), vpscal(tmp, tmp2) * 2,
			vpscal(tmp2, tmp2) - cyl.radius * cyl.radius);
	if (t[2] != -1 && cyl.angle != 0)
		return ((sqrt((double)(cyl.angle * cyl.angle) + cyl.radius * cyl.radius)
		> vsize(vsub(cyl.pos, vadd(o, vmult_dbl(dir, t[2]))))) ? t[2] : -1.0);
		return (t[2]);
}

double			inter_cone(t_obj cone, t_vector o, t_vector dir)
{
	t_norme1	n;

	n.alpha = cone.angle / 180 * M_PI / 2;
	n.origin = vsub(o, cone.pos);
	n.dir_dir = vmult_dbl(cone.dir, vpscal(dir, cone.dir));
	n.o_dir = vmult_dbl(cone.dir, vpscal(n.origin, cone.dir));
	n.tmp1 = vsub(dir, n.dir_dir);
	n.tmp2 = vsub(n.origin, n.o_dir);
	n.ret = solve_quad(pow(cos(n.alpha), 2) * vpscal(n.tmp1, n.tmp1) - pow(sin(\
n.alpha), 2) * pow(vpscal(dir, cone.dir), 2), 2 * (pow(cos(n.alpha), 2) * vpscal
(n.tmp1, n.tmp2)) - 2 * (pow(sin(n.alpha), 2) * vpscal(dir, cone.dir) * vpscal(\
n.origin, cone.dir)), pow(cos(n.alpha), 2) * vpscal(n.tmp2, n.tmp2) - pow(sin(\
n.alpha), 2) * pow(vpscal(n.origin, cone.dir), 2));
	if (n.ret != -1 && cone.radius != 0)
	{
		n.o_dir = vsub(cone.pos, vadd(o, vmult_dbl(dir, n.ret)));
		n.dir_dir = n.o_dir;
		vnorm(&n.dir_dir);
		if (vpscal(n.dir_dir, cone.dir) > 0 && cone.radius / cos(cone.angle / \
			360 * M_PI) > vsize(n.o_dir))
			return (n.ret);
		return (-1);
	}
	return (n.ret);
}
