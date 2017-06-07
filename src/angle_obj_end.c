
#include "../includes/rt.h"

t_vector		ft_angle_circle(t_obj p, t_vector dir_l)
{
	(void)dir_l;
	vnorm(&p.dir);
	return (p.dir);
}

t_vector		ft_angle_square(t_obj p, t_vector dir_l)
{
	(void)dir_l;
	vnorm(&p.dir);
	return (p.dir);
}
