/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/12 15:32:56 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_vector		ft_angle_sphere(t_obj s, t_vector hit)
{
	t_vector		pho;

	pho = vsub(hit, s.pos);
	vnorm(&pho);
	return (pho);
}

t_vector		ft_angle_plane(t_obj p, t_vector v1)
{
	(void)v1;
	return (p.dir);
}

t_vector		ft_angle_cylinder(t_obj obj, t_vector p_hit)
{
	t_vector	b;
	t_vector	c;
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
	if (((n2 = vpscal(c, c)) || 1) && n2 > n)
	{
		b.x = -(obj.dir.x * dist) + obj.pos.x;
		b.y = -(obj.dir.y * dist) + obj.pos.y;
		b.z = -(obj.dir.z * dist) + obj.pos.z;
	}
	b = vsub(p_hit, b);
	vnorm(&b);
	return (b);
}

t_vector		ft_angle_cone(t_obj obj, t_vector p_hit)
{
	double		x[5];
	t_vector	b;
	t_vector	c;

	x[3] = M_PI * obj.angle / 180;
	c = vsub(p_hit, obj.pos);
	x[0] = sqrt(vpscal(c, c));
	x[2] = x[0] * cos(x[3]);
	x[1] = x[2] * tan(x[3]);
	c.x = obj.dir.x * x[2] + obj.pos.x;
	c.y = obj.dir.y * x[2] + obj.pos.y;
	c.z = obj.dir.z * x[2] + obj.pos.z;
	b = vsub(p_hit, c);
	x[4] = sqrt(vpscal(b, b));
	if ((float)x[4] > (float)x[1])
	{
		c.x = obj.dir.x * -x[2] + obj.pos.x;
		c.y = obj.dir.y * -x[2] + obj.pos.y;
		c.z = obj.dir.z * -x[2] + obj.pos.z;
	}
	c = vsub(p_hit, c);
	vnorm(&c);
	return (c);
}
