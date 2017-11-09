/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:41:31 by shamdani          #+#    #+#             */
/*   Updated: 2017/11/09 13:40:00 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void				ft_nb_obj_light(t_envg *e, int o, int l)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7)
			o += 5;
		else if (parse_obj_b->obj.type == 8)
			o++;
		else if (parse_obj_b->obj.type == 9)
			o += 2;
		parse_obj_b = parse_obj_b->next;
		o++;
	}
	e->e->nb_obj = o;
	while (parse_light_b)
	{
		parse_light_b = parse_light_b->next;
		l++;
	}
	e->e->nb_light = l;
}

static void				ft_create_obj_light(t_envg *e, int o, int l)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7 || parse_obj_b->obj.type == 8 ||
			parse_obj_b->obj.type == 9)
			get_obj_lst(e, parse_obj_b->obj, &o);
		else
		{
			e->e->l_obj[o] = parse_obj_b->obj;
			e->e->l_obj[o].id = o + 1;
		}
		o++;
		parse_obj_b = parse_obj_b->next;
	}
	while (parse_light_b)
	{
		e->e->light[l++] = parse_light_b->light;
		parse_light_b = parse_light_b->next;
	}
}

void					ft_creat_lst_obj(t_envg *e)
{
	ft_nb_obj_light(e, 0, 0);
	if (!(e->e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->e->nb_obj)))
		ft_error(MALLOC, "e->e->l_obj -> rt.h");
	if (!(e->e->light = (t_light *)malloc(sizeof(t_light) * e->e->nb_light)))
		ft_error(MALLOC, "e->e->light -> rt.h");
	ft_create_obj_light(e, 0, 0);
}
