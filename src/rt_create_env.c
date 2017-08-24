/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:41:31 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 12:07:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			ft_creat_lst_obj(t_envg *e)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;
	int 				i;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7)
			i += 5;
		else if (parse_obj_b->obj.type == 8)
			i++;
		else if (parse_obj_b->obj.type == 9)
			i += 2;
		parse_obj_b = parse_obj_b->next;
		i++;
	}
	e->e->nb_obj = i;
	i = 0;
	while (parse_light_b)
	{
		parse_light_b = parse_light_b->next;
		i++;
	}
	e->e->nb_light = i;
	if (!(e->e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->e->nb_obj)))
		ft_error(MALLOC, "e->e->l_obj -> rt.h");
	if (!(e->e->light = (t_light *)malloc(sizeof(t_light) * e->e->nb_light)))
		ft_error(MALLOC, "e->e->light -> rt.h");
	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7 || parse_obj_b->obj.type == 8 ||
			parse_obj_b->obj.type == 9)
			get_obj_lst(e, parse_obj_b->obj, &i);
		else
		{
			e->e->l_obj[i] = parse_obj_b->obj;
			e->e->l_obj[i].id = i + 1;
		}
		i++;
		parse_obj_b = parse_obj_b->next;
	}
	i = 0;
	while (parse_light_b)
	{
		e->e->light[i] = parse_light_b->light;
		parse_light_b = parse_light_b->next;
		i++;
	}
}