/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/30 15:32:54 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		ft_raytracer2(t_env *e, t_ray ray, t_three **three, t_stuff n)
{
	if (ray.coef * (1 - e->l_obj[n.id].ind_transp) * (1 - e->l_obj[n.id].
ind_reflec) > 0.039)
		(*(e->nb_obj_pix))[e->start]++;
	if (e->l_obj[n.id].ind_reflec > 0)
	{
		n.vec = get_reflec(n.v_norm, ray.v_ray);
		ft_raytracer(e, (t_ray){n.p_hit, n.vec, ray.prof + 1, ray.coef * e->
l_obj[n.id].ind_reflec, ray.c_origin}, &((*three)->r_reflec));
	}
	if (e->l_obj[n.id].ind_transp > 0)
	{
		n.vec = (e->l_obj[n.ret].group || (e->l_obj[n.ret].type != 2 && e->
l_obj[n.ret].type != 6 && e->l_obj[n.ret].type != 5)) ? get_refrac(e, n.v_norm,
ray.v_ray, e->l_obj[n.ret].ind_refrac) : ray.v_ray;
		ft_raytracer(e, (t_ray){n.p_hit, n.vec, ray.prof + 1, ray.coef * e->
l_obj[n.id].ind_transp * (1 - e->l_obj[n.id].ind_reflec), ray.c_origin}, &((*
three)->r_refrac));
	}
	add_branch(*three, n.p_hit, ray.coef, ray.c_origin);
}

void		ft_ray_init(t_env *e, t_three **three, int *ret, int id)
{
	t_parse_obj *lst;
	t_parse_obj *tmp;

	if (!(*three = (t_three *)malloc(sizeof(t_three))))
		ft_error(MALLOC, "add_branch");
	(*three)->r_refrac = NULL;
	(*three)->r_reflec = NULL;
	(*three)->id = id + 1;
	lst = get_obj_list(e, *(e->begin_three), *three);
	*ret = ft_get_obj_neg(e->l_obj[id], lst);
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void		ft_raytracer(t_env *e, t_ray ray, t_three **three)
{
	t_vector		p_hit;
	t_vector		v_norm;
	int				id;
	int				ret;
	double			dist;

	dist = inter_obj(e, ray.p_ray, ray.v_ray, &id);
	if (ray.coef < 0.039 || dist < 0.00001 || ray.prof == 20)
	{
		*three = NULL;
		return ;
	}
	p_hit = vadd(ray.p_ray, vmult_dbl(ray.v_ray, dist));
	v_norm = return_v_norm(e->l_obj[id].type, e->l_obj[id], p_hit);
	ft_ray_init(e, three, &ret, id);
	if (ret == -1)
	{
		(*three)->id *= -1;
		ft_raytracer(e, (t_ray){p_hit, ray.v_ray, ray.prof, ray.coef,
ray.c_origin}, &((*three)->r_refrac));
		add_branch(*three, p_hit, ray.coef, ray.c_origin);
	}
	else
		ft_raytracer2(e, ray, three, (t_stuff){p_hit, (t_vector){0, 0, 0, 0}
, v_norm, id, ret});
}
