/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesprog <ldesprog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:02:07 by shamdani          #+#    #+#             */
/*   Updated: 2017/03/09 03:42:04 by ldesprog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_obj	new_sphere(t_color color, t_vector pos, double r)
{
	t_obj		obj;

	if (r < 0.1)
		ft_error(ft_strjoin(ft_itoa((int)r), " < error radius in :"), "sphere");
	obj.pos = pos;
	obj.radius = r;
	obj.type = 1;
	obj.color = color;
	obj.ind_transp = 0.5;
	return (obj);
}

static t_obj	new_plane(t_color color, t_vector dir, t_vector point)
{
	t_obj		obj;

	ft_error_var(dir, "plane -> orientation", 0);
	obj.dir = dir;
	vnorm(&obj.dir);
	obj.point = point;
	obj.type = 2;
	obj.color = color;
	obj.ind_transp = 1.0;
	return (obj);
}

static t_obj	new_cylinder(t_color co, t_vector d, t_vector po, double r)
{
	t_obj		obj;

	ft_error_var(d, "cylinder -> orientation", 0);
	if (r < 0.1)
		ft_error(ft_strjoin(ft_itoa((int)r), " < error radius in :"), "cyl...");
	obj.dir = d;
	vnorm(&obj.dir);
	obj.pos = po;
	obj.radius = r;
	obj.type = 3;
	obj.color = co;
	obj.ind_transp = 0.5;
	return (obj);
}

static t_obj	new_cone(t_color co, t_vector dir, t_vector pos, double a)
{
	t_obj		obj;

	if (a > 89 || a < 1)
		ft_error(ft_strjoin(ft_itoa((int)a), " <-- error angle in :"), "cone");
	ft_error_var(dir, "cone -> orientation", 0);
	obj.dir = dir;
	vnorm(&obj.dir);
	obj.pos = pos;
	obj.angle = a;
	obj.type = 4;
	obj.color = co;
	obj.ind_transp = 0.75;
	return (obj);
}

t_obj			add_obj(char **line, int len, int count)
{
	t_color		c;
	t_vector	pos;
	t_vector	dir;

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
	return (new_cylinder(c, pos, pos, 10.0));
}
