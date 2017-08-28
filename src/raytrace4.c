/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 16:41:46 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		get_obj_list2(t_env *e, t_three *current, t_parse_obj **rez)
{
	t_parse_obj		*tmp;

	(tmp = (t_parse_obj*)malloc(sizeof(t_parse_obj))) ? 0 :
	ft_error(MALLOC, "t_parse_obj");
	current->id < 0 ? tmp->obj = e->l_obj[-current->id - 1] :
(tmp->obj = e->l_obj[current->id - 1]);
	tmp->next = *rez;
	*rez = tmp;
}

t_parse_obj	*get_obj_list(t_env *e, t_three *current, t_three *branch)
{
	t_parse_obj	*rez;
	t_obj		obj;
	int			search;
	int			i;

	rez = NULL;
	i = 0;
	search = 1;
	while (branch != current && !current->r_refrac)
		current = current->r_reflec;
	while (branch != current)
	{
		current->id < 0 ? obj = e->l_obj[-current->id - 1] :
(obj = e->l_obj[current->id - 1]);
		if ((search = search_obj(&rez, obj)) == 1 && ((obj.type != 2 &&
			obj.type != 6 && obj.type != 5) || obj.group))
			get_obj_list2(e, current, &rez);
		current = current->r_refrac;
		while (branch != current && !current->r_refrac)
			current = current->r_reflec;
	}
	return (rez);
}

int			ft_get_obj_neg(t_obj obj, t_parse_obj *list_obj)
{
	t_parse_obj *tmp;

	tmp = list_obj;
	if (obj.negatif == 0)
	{
		while (list_obj)
		{
			if (list_obj->obj.negatif == 1)
				return (-1);
			list_obj = list_obj->next;
		}
	}
	return (obj.id - 1);
}
