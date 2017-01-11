/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:02:07 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/19 17:43:55 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_obj	*new_sphere(t_color *color, t_vector *pos, double r)
{
	t_obj		*obj;
	t_sphere	*s;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error(MALLOC, "(sphere=>obj)-(add_obj.c)");
	if (!(s = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_error(MALLOC, "(sphere=>sphere)-(add_obj.c)");
	if (r < 0.1)
		ft_error(ft_strjoin(ft_itoa((int)r), " < error radius in :"), "sphere");
	s->pos = pos;
	s->radius = r;
	obj->inter_func = inter_sphere;
	obj->angle_func = ft_angle_sphere;
	obj->obj = s;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

static t_obj	*new_plane(t_color *color, t_vector *dir, t_vector *point)
{
	t_obj		*obj;
	t_plane		*p;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error(MALLOC, "(plane=>obj)-(add_obj.c)");
	if (!(p = (t_plane *)malloc(sizeof(t_plane))))
		ft_error(MALLOC, "(plane=>plane)-(add_obj.c)");
	ft_error_var(dir, "plane -> orientation", 0);
	p->dir = dir;
	vnorm(p->dir);
	p->point = point;
	obj->inter_func = inter_plane;
	obj->angle_func = ft_angle_plane;
	obj->obj = p;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

static t_obj	*new_cylinder(t_color *co, t_vector *d, t_vector *po, double r)
{
	t_obj		*obj;
	t_cyl		*c;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error(MALLOC, "(plane=>obj)-(add_obj.c)");
	if (!(c = (t_cyl *)malloc(sizeof(t_cyl))))
		ft_error(MALLOC, "(cylindre=>cylindre)-(add_obj.c)");
	ft_error_var(d, "cylinder -> orientation", 0);
	if (r < 0.1)
		ft_error(ft_strjoin(ft_itoa((int)r), " < error radius in :"), "cyl...");
	c->dir = d;
	vnorm(c->dir);
	c->pos = po;
	c->radius = r;
	obj->inter_func = inter_cylinder;
	obj->angle_func = ft_angle_cylinder;
	obj->obj = c;
	obj->color = co;
	obj->next = NULL;
	return (obj);
}

static t_obj	*new_cone(t_color *co, t_vector *dir, t_vector *pos, double a)
{
	t_obj		*obj;
	t_cone		*c;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error(MALLOC, "(plane=>obj)-(add_obj.c)");
	if (!(c = (t_cone *)malloc(sizeof(t_cone))))
		ft_error(MALLOC, "(cylinder=>cyl)-(add_obj.c)");
	if (a > 89 || a < 1)
		ft_error(ft_strjoin(ft_itoa((int)a), " <-- error angle in :"), "cone");
	ft_error_var(dir, "cone -> orientation", 0);
	c->dir = dir;
	vnorm(c->dir);
	c->pos = pos;
	c->angle = a;
	c->m = 1;
	obj->inter_func = inter_cone;
	obj->angle_func = ft_angle_cone;
	obj->obj = c;
	obj->color = co;
	obj->next = NULL;
	return (obj);
}

t_obj			*add_obj(char **line, int len, int count)
{
	t_color		*c;
	t_vector	*pos;
	t_vector	*dir;

	c = get_color(ft_atoi(line[1]), ft_atoi(line[2]), ft_atoi(line[3]));
	pos = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	if (len == 8 && ft_strcmp(line[0], "sphere") == 0)
		return (new_sphere(c, pos, ft_atof(line[7])));
	else if (len == 10 && ft_strcmp(line[0], "plane") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_plane(c, dir, pos));
	}
	else if (len == 11 && ft_strcmp(line[0], "cone") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_cone(c, dir, pos, ft_atof(line[10])));
	}
	else if (len == 11 && ft_strcmp(line[0], "cylinder") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_cylinder(c, dir, pos, ft_atof(line[10])));
	}
	ft_error(ft_strjoin(ft_itoa(count), " < line error :"), "syntax error");
	return (NULL);
}
