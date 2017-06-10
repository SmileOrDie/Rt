/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:24:58 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/10 16:25:02 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static t_obj	new_circle(t_color2 color, t_vector dir, t_vector point, char **line)
{
	t_obj		obj;

	ft_error_var(dir, "cercle -> orientation", 0);
	obj.dir = dir;
	vnorm(&obj.dir);
	obj.pos = point;
	obj.radius = ft_atof(line[10]);
	obj.type = 5;
	obj.color = color;
	obj.ind_transp = ft_atof(line[11]);
	obj.ind_refrac = ft_atof(line[12]);
	obj.ind_reflec = ft_atof(line[13]);
	obj.name = (!line[14]) ? "circle" : ft_strdup(line[14]);
	return (obj);
}

t_obj			add_obj_end(char **line, int len, int count)
{
	t_color2		c;
	t_vector	pos;
	t_vector	dir;

	c = (t_color2){ft_atoi(line[1]), ft_atoi(line[2]), ft_atoi(line[3]), 0};
	pos = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	if ((len == 14 || len == 13) && ft_strcmp(line[0], "circle") == 0)
	{
		dir = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
		return (new_circle(c, dir, pos, line));
	}
	ft_error(ft_strjoin(ft_itoa(count), " < line error :"), "syntax error");
	return (new_circle(c, (t_vector){0, 0, 0, 0}, pos, line));
}
