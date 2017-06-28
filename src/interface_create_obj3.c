/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:00:40 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 14:18:53 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void				creat_light(t_envg *e)
{
	t_parse_light *b;
	t_parse_light *new;

	if (!(new = (t_parse_light *)malloc(sizeof(t_parse_light))))
		ft_error(MALLOC, "new_l -> inteface_create_obj.h");
	new->light = new_light(e);
	new->next = NULL;
	b = e->e->parse_light;
	if (b)
	{
		while (b->next)
			b = b->next;
		b->next = new;
	}
	else
		e->e->parse_light = new;
}

t_obj				new_obj2(t_envg *e, t_obj obj)
{
	obj.id = e->e->nb_obj;
	obj.radius = ft_atof(e->line[12]);
	obj.ind_refrac = ft_atof(e->line[14]);
	obj.ind_reflec = ft_atof(e->line[15]);
	obj.angle = ft_atof(e->line[31]);
	obj.name = ft_strdup(e->line[2]);
	obj.ind_transp = ft_atof(e->line[13]);
	obj.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]), \
		ft_atoi(e->line[11]), 0};
	obj.pos = new_v(ft_atof(e->line[3]), ft_atof(e->line[4]), \
	ft_atof(e->line[5]));
	obj.dir = new_v(ft_atof(e->line[6]), ft_atof(e->line[7]), \
	ft_atof(e->line[8]));
	obj.id_texture = e->line[30][0];
	obj.negatif = e->line[30][1];
	obj.group = (!ft_strcmp(e->line[1], "cube")) ? e->e->group_max++ : 0;
	e->e->nb_obj++;
	return (obj);
}

t_obj				new_obj(t_envg *e)
{
	t_obj obj;

	(!ft_strcmp(e->line[1], "sphere")) ? obj.type = 1 : 0;
	(!ft_strcmp(e->line[1], "plane")) ? obj.type = 2 : 0;
	(!ft_strcmp(e->line[1], "cylinder")) ? obj.type = 3 : 0;
	(!ft_strcmp(e->line[1], "cone")) ? obj.type = 4 : 0;
	(!ft_strcmp(e->line[1], "circle")) ? obj.type = 5 : 0;
	(!ft_strcmp(e->line[1], "square")) ? obj.type = 6 : 0;
	(!ft_strcmp(e->line[1], "cube")) ? obj.type = 7 : 0;
	(!ft_strcmp(e->line[1], "cone_l")) ? obj.type = 8 : 0;
	(!ft_strcmp(e->line[1], "cylinder_l")) ? obj.type = 9 : 0;
	obj = new_obj2(e, obj);
	return (obj);
}
