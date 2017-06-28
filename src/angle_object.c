/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/28 11:35:55 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_vector	ft_angle_plane(t_obj p, t_vector v1)
{
	(void)v1;
	return (p.dir);
}

void		ft_angle_cylinder2(t_obj obj, t_vector b, float dist)
{
	b.x = obj.dir.x * dist + obj.pos.x;
	b.y = obj.dir.y * dist + obj.pos.y;
	b.z = obj.dir.z * dist + obj.pos.z;
}

t_vector	ft_angle_cylinder(t_obj obj, t_vector p_hit)
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
	ft_angle_cylinder2(obj, b, dist);
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

void		ft_angle_cone2(t_vector c, double alpha, t_obj obj, t_vector p_hit)
{
	double		dist;
	double		adj;
	t_vector	b;
	double		opp;
	double		hypo;

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
}

t_vector	ft_angle_cone(t_obj obj, t_vector p_hit)
{
	t_vector	c;
	double		alpha;

	alpha = M_PI * obj.angle / 180;
	c = vsub(p_hit, obj.pos);
	ft_angle_cone2(c, alpha, obj, p_hit);
	c = vsub(p_hit, c);
	vnorm(&c);
	return (c);
}
