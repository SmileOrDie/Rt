/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:49:52 by phmoulin          #+#    #+#             */
/*   Updated: 2017/11/08 19:10:38 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_obj	g_def_object = {0, 0, 0, 0, {0, 0, 0, 0}, {1, 0, 0, 0},
	{0, 0, 0, 0}, 0, 0, 0, 0, NULL, {255, 255, 255, 255}, 0, 0, 0};

static t_obj	new_obj_2(t_envg *e, t_obj *obj)
{
	obj->ind_refrac = (obj->negatif != 0) ? 1 :
		ft_clamp(ft_atod(e->line[14]), 1, 3);
	obj->ind_reflec = (obj->negatif != 0) ? 0 :
		ft_clamp(ft_atod(e->line[15]), 0, 1);
	obj->ind_transp = (obj->negatif != 0) ? 1 :
		ft_clamp(ft_atod(e->line[13]), 0, 1);
	obj->name = e->line[2][0] ? ft_strdup(e->line[2]) : ft_strdup("n/a");
	obj->color = (obj->negatif == 1) ? (t_color2){255, 255, 255, 0} : (t_color2)
		{ft_clamp(ft_atoi(e->line[9]), 0, 255),
		ft_clamp(ft_atoi(e->line[10]), 0, 255),
		ft_clamp(ft_atoi(e->line[11]), 0, 255), 0};
	return (*obj);
}

t_obj			new_obj(t_envg *e)
{
	t_obj			obj;

	obj = g_def_object;
	check_new_obj(e, &obj);
	obj.id = e->nb_obj;
	obj.negatif = e->line[30][1];
	obj.radius = ft_atod(e->line[12]);
	obj.angle = ft_atod(e->line[31]);
	obj.pos = new_v(ft_atod(e->line[3]), ft_atod(e->line[4]),
		ft_atod(e->line[5]));
	obj.dir = new_v(ft_atod(e->line[6]), ft_atod(e->line[7]),
		ft_atod(e->line[8]));
	obj.id_texture = (obj.negatif > 0) ? 0 : e->line[30][0];
	obj.group = (!ft_strcmp(e->line[1], "cube") ||
		!ft_strcmp(e->line[1], "cone_l") ||
		!ft_strcmp(e->line[1], "cylinder_l")) ? e->group_max++ : 0;
	vnorm(&obj.dir);
	e->nb_obj++;
	return (new_obj_2(e, &obj));
}
