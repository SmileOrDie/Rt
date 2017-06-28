/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:23:00 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 15:34:41 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			del_light(t_envg *e, int i)
{
	t_parse_light *b;
	t_parse_light *f_l;

	b = e->e->parse_light;
	f_l = srch_light(e, i);
	if (i > 0)
	{
		del_light2(b, f_l);
	}
	else if (i == 0)
	{
		if (f_l == b)
			e->e->parse_light = e->e->parse_light->next;
		free(b->light.name);
		free(b);
	}
}

void			init_id(t_env *e)
{
	int			i;
	t_parse_obj	*b;

	i = 0;
	b = e->parse_obj;
	if (b)
	{
		e->parse_obj->obj.id = 0;
		while (b)
		{
			b->obj.id = i++;
			b = b->next;
		}
	}
	e->nb_obj = i;
}

void			del_obj2(t_parse_obj *b, t_parse_obj *obj)
{
	t_parse_obj *f_obj;

	while (b->next)
	{
		if (obj->obj.id == b->next->obj.id)
		{
			f_obj = b->next;
			b->next = f_obj->next;
			free(f_obj->obj.name);
			free(f_obj);
			break ;
		}
		b = b->next;
	}
}

void			del_obj(t_envg *e, int i)
{
	t_parse_obj *b;
	t_parse_obj	*obj;

	obj = srch_obj(e, i);
	b = e->e->parse_obj;
	if (i > 0)
		del_obj2(b, obj);
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
