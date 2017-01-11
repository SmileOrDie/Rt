/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:21:56 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 17:49:20 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void			add_cam(char **line, t_env *e)
{
	if (!(e->cam = (t_cam *)malloc(sizeof(t_cam))))
		ft_error(MALLOC, "(=> e->cam)-(parse.c)");
	e->cam->eye = new_v(ft_atof(line[1]), ft_atof(line[2]), ft_atof(line[3]));
	e->cam->l_at = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	e->cam->up = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
	vnorm(e->cam->up);
	e->cam->fov = ft_atoi(line[10]);
	e->cam->dist = ft_atoi(line[11]);
	e->cam->n = vsub(e->cam->eye, e->cam->l_at);
	vnorm(e->cam->n);
	e->cam->u = new_v(e->cam->up->y * e->cam->n->z - e->cam->up->z *
		e->cam->n->y, e->cam->up->z * e->cam->n->x - e->cam->up->x *
		e->cam->n->z, e->cam->up->x * e->cam->n->y - e->cam->up->y *
		e->cam->n->x);
	e->cam->h = tan(M_PI * (e->cam->fov / 2) / 180) * 2 * e->cam->dist;
	e->cam->w = e->cam->h * ((float)e->mlx->w / e->mlx->h);
	e->cam->c = new_v(e->cam->eye->x - e->cam->n->x * e->cam->dist,
		e->cam->eye->y - e->cam->n->y * e->cam->dist,
		e->cam->eye->z - e->cam->n->z * e->cam->dist);
	e->cam->l = new_v(e->cam->c->x - e->cam->u->x * (e->cam->w / 2) -
		e->cam->up->x * (e->cam->h / 2), e->cam->c->y - e->cam->u->y *
		(e->cam->w / 2) - e->cam->up->y * (e->cam->h / 2),
		e->cam->c->z - e->cam->u->z * (e->cam->w / 2) - e->cam->up->z *
		(e->cam->h / 2));
}

static void			add_light(char **line, t_env *e)
{
	t_light *light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		ft_error(MALLOC, "(=> e->light)-(parse.c)");
	light->pos = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	light->color = new_v(ft_atof(line[1]) * ft_atof(line[7]), ft_atof(line[2])
	* ft_atof(line[7]), ft_atof(line[3]) * ft_atof(line[7]));
	light->angle = 1;
	light->next = NULL;
	if (!e->light)
	{
		e->d_light = light;
		e->light = light;
	}
	else
	{
		e->light->next = light;
		e->light = e->light->next;
	}
}

void				add_env(char **line, t_env *e)
{
	if (ft_strcmp(line[0], "light") == 0)
		add_light(line, e);
	else if (ft_strcmp(line[0], "cam") == 0)
	{
		e->flag = 1;
		add_cam(line, e);
	}
	else if (ft_strcmp(line[0], "ambient") == 0)
		e->amb = ft_atof(line[1]);
}
