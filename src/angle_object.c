/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 21:28:35 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:04:11 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include "../includes/angle_obj.h"

void			ft_angle_sphere(void *env, t_vector *hit, t_vector *dir_l)
{
	t_vector	pho;
	double		tmp;
	t_env		*e;
	t_sphere	*s;

	e = (t_env *)env;
	s = (t_sphere *)e->obj->obj;
	pho = vsub2(hit, s->pos);
	vnorm(&pho);
	e->light->norm = pho;
	tmp = vpscal(&pho, dir_l);
	e->light->angle = (tmp < 0) ? 0 : tmp;
}

void			ft_angle_plane(void *env, t_vector *hit, t_vector *dir_l)
{
	t_env		*e;
	t_plane		*p;
	double		tmp;

	(void)hit;
	e = (t_env *)env;
	p = (t_plane *)e->obj->obj;
	e->light->norm = *(p->dir);
	tmp = vpscal(p->dir, dir_l);
	e->light->angle = (tmp < 0) ? tmp * -1 : tmp;
}

void			ft_angle_cylinder(void *t, t_vector *p_hit, t_vector *l_vector)
{
	t_aoc		c;

	c.e = (t_env *)t;
	c.obj = ((t_cyl *)c.e->obj->obj);
	c.b = vsub2(p_hit, c.obj->pos);
	c.n = vpscal(&c.b, &c.b);
	if ((float)c.n == c.obj->radius * c.obj->radius)
		c.dist = 0;
	else
		c.dist = sqrt(c.n - c.obj->radius * c.obj->radius);
	c.b.x = c.obj->dir->x * c.dist + c.obj->pos->x;
	c.b.y = c.obj->dir->y * c.dist + c.obj->pos->y;
	c.b.z = c.obj->dir->z * c.dist + c.obj->pos->z;
	c.c = vsub2(p_hit, &c.b);
	c.n2 = vpscal(&c.c, &c.c);
	if (c.n2 > c.n)
	{
		c.b.x = -(c.obj->dir->x * c.dist) + c.obj->pos->x;
		c.b.y = -(c.obj->dir->y * c.dist) + c.obj->pos->y;
		c.b.z = -(c.obj->dir->z * c.dist) + c.obj->pos->z;
	}
	c.e->light->norm = vsub2(p_hit, &c.b);
	vnorm(&c.e->light->norm);
	c.tmp = vpscal(&c.e->light->norm, l_vector);
	c.e->light->angle = (c.tmp < 0) ? c.tmp * -1 : c.tmp;
}

void			ft_angle_cone(void *env, t_vector *p_hit, t_vector *l_vector)
{
	t_aoco		c;

	c.e = (t_env *)env;
	c.obj = (t_cone *)c.e->obj->obj;
	c.alpha = M_PI * c.obj->angle / 180;
	c.c = vsub2(p_hit, c.obj->pos);
	c.hypo = sqrt(vpscal(&c.c, &c.c));
	c.adj = c.hypo * cos(c.alpha);
	c.opp = c.adj * tan(c.alpha);
	c.c.x = c.obj->dir->x * c.adj + c.obj->pos->x;
	c.c.y = c.obj->dir->y * c.adj + c.obj->pos->y;
	c.c.z = c.obj->dir->z * c.adj + c.obj->pos->z;
	c.b = vsub2(p_hit, &c.c);
	c.dist = sqrt(vpscal(&c.b, &c.b));
	if ((float)c.dist > (float)c.opp)
	{
		c.c.x = c.obj->dir->x * -c.adj + c.obj->pos->x;
		c.c.y = c.obj->dir->y * -c.adj + c.obj->pos->y;
		c.c.z = c.obj->dir->z * -c.adj + c.obj->pos->z;
	}
	c.e->light->norm = vsub2(p_hit, &c.c);
	vnorm(&c.e->light->norm);
	c.e->light->angle = ft_clamp_min(vpscal(&c.e->light->norm, l_vector), 0);
}
