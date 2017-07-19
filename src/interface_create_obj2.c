/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:24:19 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/12 18:39:35 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_parse_obj		*srch_obj(t_envg *e, int id)
{
	t_parse_obj *obj_lst;

	obj_lst = e->e->parse_obj;
	while (obj_lst)
	{
		if (obj_lst->obj.id == id)
			return (obj_lst);
		obj_lst = obj_lst->next;
	}
	return (NULL);
}

t_parse_light	*srch_light(t_envg *e, int id)
{
	t_parse_light	*light_lst;
	int				index;

	index = 0;
	light_lst = e->e->parse_light;
	while (light_lst)
	{
		if (index == id)
			return (light_lst);
		light_lst = light_lst->next;
		index++;
	}
	return (NULL);
}

void			reset_line(char **line)
{
	int				i;
	int				len;

	i = 0;
	while (++i <= 15)
	{
		len = ft_strlen(line[i]);
		while (len >= 0)
			line[i][len--] = '\0';
	}
	len = ft_strlen(line[31]);
	while (len >= 0)
		line[31][len--] = '\0';
}

t_light			new_light(t_envg *e)
{
	t_light			l;

	l.pos = new_v(ft_atof(e->line[3]), ft_atof(e->line[4]),
		ft_atof(e->line[5]));
	l.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]),
		ft_atoi(e->line[11]), 0};
	l.name = ft_strdup(e->line[2]);
	return (l);
}

t_obj			new_obj(t_envg *e)
{
	t_obj			obj;

	check_new_obj(e, &obj);
	obj.id = e->e->nb_obj;
	obj.radius = ft_atof(e->line[12]);
	obj.ind_refrac = ft_atof(e->line[14]);
	obj.ind_reflec = ft_atof(e->line[15]);
	obj.angle = ft_atof(e->line[31]);
	obj.name = ft_strdup(e->line[2]);
	obj.ind_transp = ft_atof(e->line[13]);
	obj.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]),
		ft_atoi(e->line[11]), 0};
	obj.pos = new_v(ft_atof(e->line[3]), ft_atof(e->line[4]),
		ft_atof(e->line[5]));
	obj.dir = new_v(ft_atof(e->line[6]), ft_atof(e->line[7]),
		ft_atof(e->line[8]));
	obj.id_texture = e->line[30][0];
	obj.negatif = e->line[30][1];
	obj.group = (!ft_strcmp(e->line[1], "cube")) ? e->e->group_max++ : 0;
	e->e->nb_obj++;
	return (obj);
}
