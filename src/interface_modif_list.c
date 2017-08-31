/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modif_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 18:35:52 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/26 16:15:38 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		modif_list_2(t_envg *e, t_parse_obj *obj_s)
{
	ft_strcpy_nbr(&(e->line[3]), obj_s->obj.pos.x);
	ft_strcpy_nbr(&(e->line[4]), obj_s->obj.pos.y);
	ft_strcpy_nbr(&(e->line[5]), obj_s->obj.pos.z);
	ft_strcpy_nbr(&(e->line[6]), obj_s->obj.dir.x);
	ft_strcpy_nbr(&(e->line[7]), obj_s->obj.dir.y);
	ft_strcpy_nbr(&(e->line[8]), obj_s->obj.dir.z);
	ft_strcpy_nbr(&(e->line[9]), obj_s->obj.color.r);
	ft_strcpy_nbr(&(e->line[10]), obj_s->obj.color.g);
	ft_strcpy_nbr(&(e->line[11]), obj_s->obj.color.b);
	ft_strcpy_nbr(&(e->line[12]), obj_s->obj.radius);
	ft_strcpy_nbr(&(e->line[13]), obj_s->obj.ind_transp);
	ft_strcpy_nbr(&(e->line[14]), obj_s->obj.ind_refrac);
	ft_strcpy_nbr(&(e->line[15]), obj_s->obj.ind_reflec);
}

void			modif_list(t_envg *e, int obj)
{
	char			*type_obj[15];
	t_parse_obj		*obj_s;

	type_obj[0] = "sphere";
	type_obj[1] = "plane";
	type_obj[2] = "cylinder";
	type_obj[3] = "cone";
	type_obj[4] = "circle";
	type_obj[5] = "square";
	type_obj[6] = "cube";
	type_obj[7] = "cone_l";
	type_obj[8] = "cylinder_l";
	load_img(e, 3);
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	obj_s = srch_obj(e, obj);
	modif_list_2(e, obj_s);
	ft_strcpy(e->line[1], type_obj[(obj_s->obj.type - 1)]);
	ft_strcpy(e->line[2], obj_s->obj.name);
	e->line[30][0] = obj_s->obj.id_texture;
	e->line[30][1] = obj_s->obj.negatif;
	ft_strcpy_nbr(&(e->line[31]), obj_s->obj.angle);
	conf_tab(e);
}
