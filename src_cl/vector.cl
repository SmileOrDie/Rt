double		ft_clamp_min(double a, double b)
{
	double r;

	r = (a < b) ? b : a;
	return (r);
}

double		ft_clamp_max(double a, double b)
{
	double r;

	r = (a > b) ? b : a;
	return (r);
}

double		ft_clamp(double a, double b, double c)
{
	double r;

	r = (a < b) ? b : a;
	r = (a > c) ? c : a;
	return (r);
}

double4 vcross_prod(double4 a, double4 b)
{
	double4 new;

	new.x = a.y * b.z - a.z * b.y;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}

double4	new_v(double x, double y, double z)
{
	double4 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double4	vrot(double4 u, double angle, double4 point)
{
	double4		r;
	double		c;
	double		s;
	double		mat[3][3];

	c = cos(angle / 360 * 2 * M_PI);
	s = sin(angle / 360 * 2 * M_PI);
	u = vnorm(u);
	mat[0][0] = u.x * u.x * (1 - c) + c;
	mat[0][1] = u.x * u.y * (1 - c) + u.z * s;
	mat[0][2] = u.x * u.z * (1 - c) - u.y * s;
	mat[1][0] = u.y * u.x * (1 - c) - u.z * s;
	mat[1][1] = u.y * u.y * (1 - c) + c;
	mat[1][2] = u.y * u.z * (1 - c) + u.x * s;
	mat[2][0] = u.z * u.x * (1 - c) + u.y * s;
	mat[2][1] = u.z * u.y * (1 - c) - u.x * s;
	mat[2][2] = u.z * u.z * (1 - c) + c;
	r.x = mat[0][0] * point.x +  mat[1][0] * point.y + mat[2][0] * point.z;
	r.y = mat[0][1] * point.x +  mat[1][1] * point.y + mat[2][1] * point.z;
	r.z = mat[0][2] * point.x +  mat[1][2] * point.y + mat[2][2] * point.z;
	return (r);
}

double4	vcross(double4 a, double4 b)
{
	double4 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

double4	vadd(double4 a, double4 b)
{
	double4 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

double4	vhit(double4 pos, double4 dir, double dist)
{
	double4 c;

	c.x = pos.x + dir.x * dist;
	c.y = pos.y + dir.y * dist;
	c.z = pos.z + dir.z * dist;
	return (c);
}

double4	vmult(double4 a, double4 b)
{
	double4 c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return (c);
}

double4	vmult_dbl(double4 a, double b)
{
	double4 ret;

	ret = new_v(a.x * b, a.y * b, a.z * b);
	return (ret);
}

double4	vnorm(double4 a)
{
	double		id;

	if (a.x == 0 && a.y == 0 && a.z == 0)
		id = 0;
	else
		id = 1 / sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	a.x = a.x * id;
	a.y = a.y * id;
	a.z = a.z * id;
	return (a);
}

double	vpscal(double4 a, double4 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vsize(double4 v)
{
	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (0);
	return (sqrt(vpscal(v, v)));
}

double4	vsub(double4 a, double4 b)
{
	double4 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
