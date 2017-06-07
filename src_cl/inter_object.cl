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

double			inter_sphere(t_obj sp, double4 o, double4 dir)
{
	double4		dist_s;
	double		b;
	double		d;
	double		t0;
	double		t1;
	double		a;

	dist_s = vsub(sp.pos, o);
	b = vpscal(dir, dist_s);
	d = b * b - vpscal(dist_s, dist_s) + sp.radius * sp.radius;
	if (d <= 0.00001)
		return (-1);
	a = sqrt(d);
	t0 = b - a;
	t1 = b + a;
	if (t0 > 0.00001 && (t1 < 0.00001 || t1 >= t0))
		return (t0);
	else if (t1 > 0.00001)
		return (t1);
	return (-1.0);
}

double			inter_plane(t_obj p, double4 o, double4 dir)
{
	double		d;
	double		nd;
	double		te;
	double4		qe;

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

double			inter_cylinder(t_obj cyl, double4 o, double4 dir)
{
	double		t0;
	double		t1;
	double		a;
	double		b;
	double		c;
	double4	dp;
	double4	tmp;
	double4	tmp2;

	dp = vsub(o, cyl.pos);
	t0 = vpscal(dir, cyl.dir);
	a = dir.x - t0 * cyl.dir.x;
	b = dir.y - t0 * cyl.dir.y;
	c = dir.z - t0 * cyl.dir.z;
	tmp = new_v(a, b, c);
	t1 = vpscal(dp, cyl.dir);
	a = dp.x - t1 * cyl.dir.x;
	b = dp.y - t1 * cyl.dir.y;
	c = dp.z - t1 * cyl.dir.z;
	tmp2 = new_v(a, b, c);
	return (solve_quad(vpscal(tmp, tmp), vpscal(tmp, tmp2) * 2,
			vpscal(tmp2, tmp2) - cyl.radius * cyl.radius));
}

double			inter_cone(t_obj cone, double4 o, double4 dir)
{
	double		alpha;
	double4		origin;
	double4		tmp1;
	double4		tmp2;
	double4		dir_dir;
	double4		o_dir;

	alpha = cone.angle / 180 * M_PI;
	origin = vsub(o, cone.pos);
	dir_dir = vmult_dbl(cone.dir, vpscal(dir, cone.dir));
	o_dir = vmult_dbl(cone.dir, vpscal(origin, cone.dir));
	tmp1 = vsub(dir, dir_dir);
	tmp2 = vsub(origin, o_dir);
	return (solve_quad(pow(cos(alpha), 2) * vpscal(tmp1, tmp1) -
			pow(sin(alpha), 2) * pow(vpscal(dir, cone.dir), 2),
			2 * (pow(cos(alpha), 2) * vpscal(tmp1, tmp2)) - 2 *
			(pow(sin(alpha), 2) * vpscal(dir, cone.dir) *
			vpscal(origin, cone.dir)), pow(cos(alpha), 2) *
			vpscal(tmp2, tmp2) - pow(sin(alpha), 2) *
			pow(vpscal(origin, cone.dir), 2)));
}
