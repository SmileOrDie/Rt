/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:02:07 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/20 13:48:10 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static t_obj	new_sphere(t_color2 color, t_vector pos, char **line)
{
	t_obj		obj;

	if (ft_atof(line[7]) < 0.1)
		ft_error(ft_strjoin(line[7], " < error radius in :"), "sphere");
	obj.angle = 0;
	obj.pos = pos;
	obj.radius = ft_atof(line[7]);
	obj.type = 1;
	obj.color = color;
	obj.ind_transp = ft_atof(line[8]);
	obj.ind_refrac = ft_atof(line[9]);
	obj.ind_reflec = ft_atof(line[10]);
	obj.name = (!line[11]) ? "sphere" : ft_strdup(line[11]);
	return (obj);
}



static t_obj	new_plane(t_color2 color, t_vector dir, t_vector point, char **line)
{
	t_obj		obj;

	ft_error_var(dir, "plane -> orientation", 0);
	obj.angle = 0;
	obj.radius = 0;
	obj.dir = dir;
	vnorm(&obj.dir);
	obj.pos = point;
	obj.type = 2;
	obj.color = color;
	obj.ind_transp = ft_atof(line[10]);
	obj.ind_refrac = ft_atof(line[11]);
	obj.ind_reflec = ft_atof(line[12]);
	obj.name = (!line[13]) ? "plane" : ft_strdup(line[13]);
	return (obj);
}

static t_obj	new_cylinder(t_color2 co, t_vector d, t_vector po, char **line)
{
	t_obj		obj;

	ft_error_var(d, "cylinder -> orientation", 0);
	if (ft_atof(line[10]) < 0.1)
		ft_error(ft_strjoin(line[10], " < error radius in :"), "cyl...");
	obj.angle = 0;
	obj.dir = d;
	vnorm(&obj.dir);
	obj.pos = po;
	obj.radius = ft_atof(line[10]);
	obj.type = 3;
	obj.color = co;
	obj.ind_transp = ft_atof(line[11]);
	obj.ind_refrac = ft_atof(line[12]);
	obj.ind_reflec = ft_atof(line[13]);
	obj.name = (!line[14]) ? "cylinder" : ft_strdup(line[14]);
	return (obj);
}

static t_obj	new_cone(t_color2 co, t_vector dir, t_vector pos, char **line)
{
	t_obj		obj;

	if (ft_atof(line[10]) > 89 || ft_atof(line[10]) < 1)
		ft_error(ft_strjoin(line[10], " <-- error angle in :"), "cone");
	ft_error_var(dir, "cone -> orientation", 0);
	obj.radius = 0;
	obj.dir = dir;
	vnorm(&obj.dir);
	obj.pos = pos;
	obj.angle = ft_atof(line[10]);
	obj.type = 4;
	obj.color = co;
	obj.ind_transp = ft_atof(line[11]);
	obj.ind_refrac = ft_atof(line[12]);
	obj.ind_reflec = ft_atof(line[13]);
	obj.name = (!line[14]) ? "cone" : ft_strdup(line[14]);
	return (obj);
}

t_obj			add_obj(char **line, int len, int count)
{
	t_color2	c;
	t_vector	pos;
	t_vector	dir;

	c = (t_color2){ft_atoi(line[1]), ft_atoi(line[2]), ft_atoi(line[3]), 0};
	pos = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	if ((len == 11 || len == 12) && ft_strcmp(line[0], "sphere") == 0)
		return (new_sphere(c, pos, line));
	else if ((len == 13 || len == 14) && ft_strcmp(line[0], "plane") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_plane(c, dir, pos, line));
	}
	else if ((len == 14 || len == 15) && ft_strcmp(line[0], "cone") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_cone(c, dir, pos, line));
	}
	else if ((len == 15 || len == 14) && ft_strcmp(line[0], "cylinder") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_cylinder(c, dir, pos, line));
	}
	return (add_obj_end(line, len, count));
}
