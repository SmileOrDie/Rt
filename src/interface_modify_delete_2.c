/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 18:40:27 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/27 15:28:12 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		free_light(t_parse_light *f_l, t_parse_light *b)
{
	f_l = b->next;
	b->next = f_l->next;
	free(f_l->light.name);
	free(f_l);
	f_l = NULL;
}

void			del_light(t_envg *e, int i)
{
	t_parse_light	*b;
	t_parse_light	*f_l;

	b = e->e->parse_light;
	f_l = srch_light(e, i);
	if (i > 0)
	{
		while (b->next)
		{
			if (b->next == f_l)
			{
				free_light(f_l, b);
				break ;
			}
			b = b->next;
		}
	}
	else if (i == 0)
	{
		if (f_l == b)
			e->e->parse_light = e->e->parse_light->next;
		free(b->light.name);
		free(b);
	}
}

static void		free_f_obj(t_parse_obj *b, t_parse_obj *f_obj, t_parse_obj *obj)
{
	while (obj && b->next)
	{
		if (b->next && obj->obj.id == b->next->obj.id)
		{
			f_obj = b->next;
			b->next = f_obj->next;
			// if (f_obj->obj.name)
			free(f_obj->obj.name);
			// if (f_obj)
			free(f_obj);
			break ;
		}
		b = b->next;
	}
}

void			del_obj(t_envg *e, int i)
{
	t_parse_obj	*b;
	t_parse_obj	*f_obj;
	t_parse_obj	*obj;

	f_obj = NULL;
	obj = srch_obj(e, i);
	b = e->e->parse_obj;
	if (i > 0)
		free_f_obj(b, f_obj, obj);
	else if (i == 0)
	{
		if (obj->obj.id == b->obj.id)
			e->e->parse_obj = e->e->parse_obj->next;
		free(b->obj.name);
		free(b);
		b = NULL;
	}
	init_id(e->e);
}
