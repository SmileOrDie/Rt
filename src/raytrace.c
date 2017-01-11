/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:47:49 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 18:32:05 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		inter_obj(t_env *e, t_vector *pos, t_vector *dir, double *t)
{
	t_obj		*lst;
	double		tr;

	lst = e->l_obj;
	tr = *t;
	while (lst)
	{
		if (lst->inter_func(lst->obj, pos, dir, &tr) && !e->flag)
			e->obj = lst;
		lst = lst->next;
	}
	if (tr < *t)
	{
		*t = tr;
		return (1);
	}
	return (0);
}

static void		l_color(t_env *e)
{
	double tmp;

	tmp = pow(ft_clamp(e->light->angle, 0, 1), 150) * 255;
	e->r += tmp * e->light->color->x;
	e->g += tmp * e->light->color->y;
	e->b += tmp * e->light->color->z;
	(e->r > 255) ? e->r = 255 : 0;
	(e->g > 255) ? e->g = 255 : 0;
	(e->b > 255) ? e->b = 255 : 0;
}

static void		add_light(t_env *e, double t, t_vector *phit)
{
	t_vector	dir_l;

	e->flag = 1;
	while (e->light)
	{
		dir_l = vsub2(e->light->pos, phit);
		t = sqrt(dir_l.x * dir_l.x + dir_l.y * dir_l.y + dir_l.z * dir_l.z);
		vnorm(&dir_l);
		if (!(inter_obj(e, phit, &dir_l, &t)))
		{
			e->obj->angle_func(e, phit, &dir_l);
			e->r += e->c_hit->r * e->light->color->x * e->light->angle;
			e->g += e->c_hit->g * e->light->color->y * e->light->angle;
			e->b += e->c_hit->b * e->light->color->z * e->light->angle;
			l_color(e);
		}
		else
			e->light->angle = 0;
		e->light = e->light->next;
	}
	e->flag = 0;
	e->light = e->d_light;
}

static void		ft_raytracer(int x, int y, t_env *e)
{
	t_vector	ray;
	t_vector	phit;
	t_vector	dir;
	double		t;

	ray = new_v2(e->cam->l->x + e->cam->u->x * x * (e->cam->w / e->mlx->w) + e->
		cam->up->x * y * (e->cam->h / e->mlx->h), e->cam->l->y + e->cam->u->y *
		x * (e->cam->w / e->mlx->w) + e->cam->up->y * y * (e->cam->h / e->mlx->
		h), e->cam->l->z + e->cam->u->z * x * (e->cam->w / e->mlx->w) + e->
		cam->up->z * y * (e->cam->h / e->mlx->h));
	dir = vsub2(&ray, e->cam->eye);
	vnorm(&dir);
	t = T;
	e->d_light = e->light;
	e->flag = 0;
	if (inter_obj(e, e->cam->eye, &dir, &t) && ((e->c_hit = e->obj->color) ||
		1))
	{
		e->r = e->c_hit->r * e->amb;
		e->g = e->c_hit->g * e->amb;
		e->b = e->c_hit->b * e->amb;
		phit = vhit2(e->cam->eye, &dir, t);
		add_light(e, t, &phit);
		put_pixel(x, y, e);
	}
}

void			start_ray(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->mlx->w)
	{
		y = -1;
		while (++y < e->mlx->h)
			ft_raytracer(x, y, e);
	}
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
}
