/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:43:47 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 18:30:18 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include "../includes/inter_obj.h"

int				inter_sphere(void *sp, t_vector *o, t_vector *dir, double *t)
{
	t_ios		s;

	s.dist_s = vsub2(((t_sphere *)sp)->pos, o);
	s.b = vpscal(dir, &s.dist_s);
	s.d = s.b * s.b - vpscal(&s.dist_s, &s.dist_s) + ((t_sphere *)sp)->radius *
		((t_sphere *)sp)->radius;
	if (s.d < 0.01)
		return (0);
	s.a = sqrt(s.d);
	s.t0 = s.b - s.a;
	s.t1 = s.b + s.a;
	s.result = 1;
	if (s.t0 > 0.1 && s.t0 < *t)
		*t = s.t0;
	else if (s.t1 > 0.1 && s.t1 < *t)
		*t = s.t1;
	else
		s.result = 0;
	return (s.result);
}

int				inter_plane(void *plane, t_vector *o, t_vector *dir, double *t)
{
	t_plane		*p;
	double		d;
	double		nd;
	double		te;
	t_vector	qe;

	p = (t_plane *)plane;
	qe = vsub2(p->point, o);
	d = vpscal(p->dir, &qe);
	nd = vpscal(p->dir, dir);
	if (fabs(nd) > *t)
		return (0);
	te = d / nd;
	if (te > 0.01 && te < *t)
	{
		*t = te;
		return (1);
	}
	return (0);
}

int				inter_cylinder(void *cyl, t_vector *o, t_vector *dir, double *t)
{
	t_cyl		*cy;
	t_iocy		c;

	cy = (t_cyl *)cyl;
	c.dp = vsub2(o, cy->pos);
	c.t0 = vpscal(dir, cy->dir);
	c.a = dir->x - c.t0 * cy->dir->x;
	c.b = dir->y - c.t0 * cy->dir->y;
	c.c = dir->z - c.t0 * cy->dir->z;
	c.tmp = new_v2(c.a, c.b, c.c);
	c.t1 = vpscal(&c.dp, cy->dir);
	c.a = c.dp.x - c.t1 * cy->dir->x;
	c.b = c.dp.y - c.t1 * cy->dir->y;
	c.c = c.dp.z - c.t1 * cy->dir->z;
	c.tmp2 = new_v2(c.a, c.b, c.c);
	return (solve_quad(vpscal(&c.tmp, &c.tmp), vpscal(&c.tmp, &c.tmp2) * 2,
			vpscal(&c.tmp2, &c.tmp2) - cy->radius * cy->radius, t));
}

int				inter_cone(void *co, t_vector *o, t_vector *dir, double *t)
{
	t_ioc		c;
	t_cone		*cone;

	cone = (t_cone *)co;
	c.alpha = cone->angle / 180 * M_PI;
	c.origin = vsub2(o, cone->pos);
	c.dir_dir = vmult_dbl2(cone->dir, vpscal(dir, cone->dir));
	c.o_dir = vmult_dbl2(cone->dir, vpscal(&c.origin, cone->dir));
	c.tmp1 = vsub2(dir, &c.dir_dir);
	c.tmp2 = vsub2(&c.origin, &c.o_dir);
	return (solve_quad(pow(cos(c.alpha), 2) * vpscal(&c.tmp1, &c.tmp1) -
			pow(sin(c.alpha), 2) * pow(vpscal(dir, cone->dir), 2),
			2 * (pow(cos(c.alpha), 2) * vpscal(&c.tmp1, &c.tmp2)) - 2 *
			(pow(sin(c.alpha), 2) * vpscal(dir, cone->dir) *
			vpscal(&c.origin, cone->dir)), pow(cos(c.alpha), 2) *
			vpscal(&c.tmp2, &c.tmp2) - pow(sin(c.alpha), 2) *
			pow(vpscal(&c.origin, cone->dir), 2), t));
}
