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

double4	new_v(double x, double y, double z)
{
	double4 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
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

	if (a.x + a.y + a.z == 0)
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
