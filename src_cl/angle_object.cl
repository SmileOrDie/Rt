double4		ft_angle_sphere(t_obj s, double4 hit)
{
	double4		pho;

	pho = vsub(hit, s.pos);
	pho = vnorm(pho);
	return (pho);
}

double4		ft_angle_plane(t_obj p)
{
	return (p.dir);
}

double4		ft_angle_cylinder(t_obj obj, double4 p_hit)
{
	double4	b;
	double4	c;
	double		n;
	double		n2;
	float		dist;

	b = vsub(p_hit, obj.pos);
	n = vpscal(b, b);
	if ((float)n == obj.radius * obj.radius)
		dist = 0;
	else
		dist = sqrt(n - obj.radius * obj.radius);
	b.x = obj.dir.x * dist + obj.pos.x;
	b.y = obj.dir.y * dist + obj.pos.y;
	b.z = obj.dir.z * dist + obj.pos.z;
	c = vsub(p_hit, b);
	n2 = vpscal(c, c);
	if (n2 > n)
	{
		b.x = -(obj.dir.x * dist) + obj.pos.x;
		b.y = -(obj.dir.y * dist) + obj.pos.y;
		b.z = -(obj.dir.z * dist) + obj.pos.z;
	}
	return (vnorm(vsub(p_hit, b)));
}

double4		ft_angle_cone(t_obj obj, double4 p_hit)
{
	double		hypo;
	double		opp;
	double		adj;
	double4		b;
	double4		c;
	double		alpha;
	double		dist;

	alpha = M_PI * obj.angle / 180;
	c = vsub(p_hit, obj.pos);
	hypo = sqrt(vpscal(c, c));
	adj = hypo * cos(alpha);
	opp = adj * tan(alpha);
	c.x = obj.dir.x * adj + obj.pos.x;
	c.y = obj.dir.y * adj + obj.pos.y;
	c.z = obj.dir.z * adj + obj.pos.z;
	b = vsub(p_hit, c);
	dist = sqrt(vpscal(b, b));
	if ((float)dist > (float)opp)
	{
		c.x = obj.dir.x * -adj + obj.pos.x;
		c.y = obj.dir.y * -adj + obj.pos.y;
		c.z = obj.dir.z * -adj + obj.pos.z;
	}
	return (vnorm(vsub(p_hit, c)));
}
