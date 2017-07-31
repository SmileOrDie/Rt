double2			solve_quad(double a, double b, double c, int *toucher)
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
		return ((double2){x0, x1});
	}
	*toucher = 0;
	return ((double2){0, 0});
}

double2			inter_sphere(t_obj sp, double4 o, double4 dir, int *toucher)
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
	{
		*toucher = 0;
		return ((double2){0, 0});
	}
	a = sqrt(d);
	t0 = b - a;
	t1 = b + a;
	return ((double2){t0, t1});
}

double2			inter_plane(t_obj p, double4 o, double4 dir, int *toucher)
{
	double		d;
	double		nd;
	double		te;
	double4		qe;
	double2		rez;

	rez[0] = 0;
	rez[1] = 0;
	qe = vsub(p.pos, o);
	d = vpscal(p.dir, qe);
	nd = vpscal(p.dir, dir);
	te = d / nd;
	if (nd < 0.00001 && nd > -0.00001)
	{
		*toucher = 0;
		return (rez);
	}
	return ((double2){te, 0});
}

double2			inter_cylinder(t_obj cyl, double4 o, double4 dir, int *toucher)
{
	double		t0;
	double		t1;
	double		a;
	double		b;
	double		c;
	double2		ret;
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
	ret = solve_quad(vpscal(tmp, tmp), vpscal(tmp, tmp2) * 2,
			vpscal(tmp2, tmp2) - cyl.radius * cyl.radius, toucher);
	if (*toucher == 1 && cyl.angle != 0)
	{
		if (sqrt((double)(cyl.angle * cyl.angle) + cyl.radius * cyl.radius) > vsize(vsub(cyl.pos, vadd(o, vmult_dbl(dir, ret[0])))))
			return (ret);
		*toucher = 0;
	}
	return (ret);
}

double2			inter_cone(t_obj cone, double4 o, double4 dir, int *toucher)
{
	double		alpha;
	double4	origin;
	double4	tmp1;
	double4	tmp2;
	double4	dir_dir;
	double4	o_dir;
	double2		ret;

	alpha = cone.angle / 180 * M_PI / 2;
	origin = vsub(o, cone.pos);
	dir_dir = vmult_dbl(cone.dir, vpscal(dir, cone.dir));
	o_dir = vmult_dbl(cone.dir, vpscal(origin, cone.dir));
	tmp1 = vsub(dir, dir_dir);
	tmp2 = vsub(origin, o_dir);
	ret = solve_quad(pow(cos(alpha), 2) * vpscal(tmp1, tmp1) - pow(sin(alpha),
2) * pow(vpscal(dir, cone.dir), 2), 2 * (pow(cos(alpha), 2) * vpscal(tmp1,
tmp2)) - 2 * (pow(sin(alpha), 2) * vpscal(dir, cone.dir) * vpscal(origin,
cone.dir)), pow(cos(alpha), 2) * vpscal(tmp2, tmp2) - pow(sin(alpha), 2) *
pow(vpscal( origin, cone.dir), 2), toucher);
	if (*toucher == 1 && cone.radius != 0)
	{
		o_dir = vsub(cone.pos, vadd(o, vmult_dbl(dir, ret[0])));
		dir_dir = o_dir;
		dir_dir = vnorm(dir_dir);
		if (vpscal(dir_dir, cone.dir) > 0 && cone.radius / cos(cone.angle / 360 * M_PI) > vsize(o_dir))
			return (ret);
		*toucher = 0;
	}
	return (ret);
}

double2			inter_circle(t_obj p, double4 o, double4 dir, int *toucher)
{
	double		d;
	double		nd;
	double		te;
	double4	qe;
	double2	rez;

	rez[0] = 0;
	rez[1] = 0;
	qe = vsub(p.pos, o);
	d = vpscal(p.dir, qe);
	nd = vpscal(p.dir, dir);
	te = d / nd;
	if (nd < 0.00001 && nd > -0.00001)
	{
		*toucher = 0;
		return (rez);
	}
	if (te > 0)
	{
		if (vsize(vsub(vadd(vmult_dbl(dir, te), o), p.pos)) > p.radius)
		{
			*toucher = 0;
			return (rez);
		}
		return ((double2){te, 0});
	}
	*toucher = 0;
	return (rez);
}

double2			inter_square(t_obj p, double4 o, double4 dir, int *toucher)
{
	double		d;
	double		nd;
	double		te;
	double4	p_hit;
	double4	u;
	double4	cross;
	double2	rez;

	rez[0] = 0;
	rez[1] = 0;
	d = vpscal(p.dir, vsub(p.pos, o));
	nd = vpscal(p.dir, dir);
	if (nd < 0.00001 && nd > -0.00001)
	{
		*toucher = 0;
		return (rez);
	}
	te = d / nd;
	if (te > 0)
	{
		cross = (p.dir.x == 1) ? (double4){0, 1, 0, 0} : (double4){1, 0, 0, 0};
		p_hit = vadd(o, vmult_dbl(dir, te));
		u = vsub(p_hit, p.pos);
		cross = vcross(p.dir, cross);
		cross = vrot(p.dir, p.angle, cross);
		cross = vnorm(cross);
		if (p.point.x != 0 || p.point.y != 0 || p.point.z != 0)
			cross = vnorm(p.point);
		if (vpscal(cross, u) < p.radius / 2 && vpscal(cross, u) > -p.radius / 2)
		{
			cross = vcross(cross, p.dir);
			cross = vnorm(cross);
			if (vpscal(cross, u) < p.radius / 2 && vpscal(cross, u) > -p.radius / 2)
				return ((double2){te, 0});
		}
	}
	*toucher = 0;
	return (rez);
}