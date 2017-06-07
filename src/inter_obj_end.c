
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
