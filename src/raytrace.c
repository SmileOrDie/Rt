/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 17:35:04 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

void				ft_debug(t_parse_obj *obj_list)
{
	t_parse_obj		*begin;
	int				i;

	i = 0;
	begin = obj_list;
	while (obj_list != NULL && obj_list->next != NULL)
	{
		i++;
		obj_list = obj_list->next;
	}
	obj_list = begin;
}

t_parse_obj			*get_obj_list(t_env *e, t_three *current, t_three *branch)
{
	t_norme16	n;

	n.rez = NULL;
	n.search = 1;
	while (branch != current && !current->r_refrac)
		current = current->r_reflec;
	while (branch != current)
	{
		n.obj = e->l_obj[current->id];
		n.search = search_obj(&n.rez, n.obj);
		if (n.search == 1 && n.obj.type != 2 && n.obj.type != 6 && n.obj.type != 5)
		{
			n.tmp = malloc(sizeof(t_parse_obj));
			n.tmp->obj = e->l_obj[current->id];
			n.tmp->next = n.rez;
			n.rez = n.tmp;
		}
		current = current->r_refrac;
		while (branch != current && !current->r_refrac)
			current = current->r_reflec;
	}
	return (n.rez);
}

int					ft_get_obj_neg(t_obj obj, t_parse_obj *list_obj)
{
	t_parse_obj *tmp;

	tmp = list_obj;
	if (obj.negatif == 0)
	{
		while (list_obj)
		{
			if (list_obj->obj.negatif == 1)
				return (1);
			list_obj = list_obj->next;
		}
	}
	if (obj.negatif == 1)
	{
		while (list_obj)
		{
			if (list_obj->obj.negatif == 0)
				return (1);
			list_obj = list_obj->next;
		}
	}
	return (0);
}

void				ft_raytracer(t_env *e, t_vector p_ray, t_vector v_ray, int prof,\
	double coef, t_color2 c_origin, t_three **three)
{
	t_vector		p_hit;
	t_vector		v_refrac;
	t_vector		v_reflec;
	t_vector		v_norm;
	int				id;
	double			dist;
	t_parse_obj		*obj_list;

	dist = inter_obj(e, p_ray, v_ray, &id);
	if (coef < 0.04 || dist < 0.00001 || prof == 20)
	{
		*three = NULL;
		return ;
	}
	p_hit = vadd(p_ray, vmult_dbl(v_ray, dist));
	v_norm = return_v_norm(e->l_obj[id].type, e->l_obj[id], p_hit);
	if (!(*three = (t_three *)malloc(sizeof(t_three))))
		ft_error(MALLOC, "add_branch");
	(*three)->r_refrac = NULL;
	(*three)->r_reflec = NULL;
	(*three)->id = id;
	obj_list = get_obj_list(e, *(e->begin_three), *three);
	if (ft_get_obj_neg(e->l_obj[id], obj_list))
	{
		free(*three);
		ft_raytracer(e, p_hit, v_ray, prof, coef, c_origin, three);
	}
	else
	{
		if (coef * (1 - e->l_obj[id].ind_transp) * \
		(1 - e->l_obj[id].ind_reflec) > 0.039)
			(*(e->nb_obj_pix))[e->start]++;
		if (e->l_obj[id].ind_reflec > 0)
		{
			v_reflec = get_reflec(v_norm, v_ray);
			ft_raytracer(e, p_hit, v_reflec, prof + 1, coef * \
				e->l_obj[id].ind_reflec, c_origin, &((*three)->r_reflec));
		}
		if (e->l_obj[id].ind_transp > 0)
		{
			c_origin.r = e->l_obj[id].color.r * c_origin.r / 255.0;
			c_origin.g = e->l_obj[id].color.g * c_origin.g / 255.0;
			c_origin.b = e->l_obj[id].color.b * c_origin.b / 255.0;
			v_refrac = (e->l_obj[id].type != 2 && e->l_obj[id].type != 6 && \
				e->l_obj[id].type != 5) ? get_refrac(e, v_norm, v_ray, \
					e->l_obj[id].ind_refrac) : v_ray;
			ft_raytracer(e, p_hit, v_refrac, prof + 1, coef * \
				e->l_obj[id].ind_transp * (1 - e->l_obj[id].ind_reflec), \
				c_origin, &((*three)->r_refrac));
		}
		add_branch(*three, p_hit, coef, c_origin);
	}
}
