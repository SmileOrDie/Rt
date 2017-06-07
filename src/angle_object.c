/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/28 15:36:18 by shamdani         ###   ########.fr       */
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
	n2 = vpscal(c, c);
	if (n2 > n)
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
	double		hypo;
	double		opp;
	double		adj;
	t_vector	b;
	t_vector	c;
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
	c = vsub(p_hit, c);
	vnorm(&c);
	return (c);
}
