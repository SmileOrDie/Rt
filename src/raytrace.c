/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/04 19:37:26 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	return_dist(t_obj obj, t_vector p_ray, t_vector v_ray)
{
	static double (*inter[6])(t_obj, t_vector, t_vector) = {inter_sphere, inter_plane, inter_cylinder, inter_cone, inter_circle, inter_square};

	return (inter[obj.type - 1](obj, p_ray, v_ray));
}

double		inter_obj(t_env *e, t_vector p_ray, t_vector v_ray, int *id)
{
	int			i;
	double		short_dist;
	double		dist;

	i = 0;
	short_dist = -1;
	while (i < e->nb_obj)
	{
		dist = return_dist(e->l_obj[i], p_ray, v_ray);
		if (dist >= 0.01 && (short_dist > dist || short_dist == -1))
		{
			*id = i;
			short_dist = dist;
		}
		i++;
	}
	return (short_dist);
}

t_vector		get_refrac(t_env *e, t_vector v_norm, t_vector v_dir, double ind_refrac)
{
	double		c1;
	double		c2;
	t_vector	ret;
	double		n;

	if (e->actual_indice != ind_refrac)
		n = e->actual_indice / ind_refrac;
	else
		n = e->actual_indice / e->default_indice;
	n > 1 ? n = pow(n, -1) : 0;
	c1 = vpscal(v_norm, vmult_dbl(v_dir, -1));
	c2 = sqrt(1 - n * n * (1 - c1 * c1));
	if (e->actual_indice != ind_refrac)
		e->actual_indice = ind_refrac;
	else
		e->actual_indice = e->default_indice;
	if (c1 > 0)
		ret = vadd(vmult_dbl(v_dir, n), vmult_dbl(v_norm, (n * c1 - c2)));
	else
		ret = vadd(vmult_dbl(v_dir, n), vmult_dbl(v_norm, (n * c1 + c2)));
	return (ret);
}

t_vector		get_reflec(t_vector v_norm, t_vector v_dir)
{
	double c1;

	c1 = vpscal(v_norm, vmult_dbl(v_dir, -1));
	return (vadd(v_dir, vmult_dbl(v_norm, 2 * c1)));
}

t_color2		add_color(t_color2 c1, t_color2 c2)
{
	t_color2	rez;

	rez.r = c1.r + c2.r;
	rez.g = c1.g + c2.g;
	rez.b = c1.b + c2.b;
	return (rez);
}

t_color2		l_shine(t_color2 c, t_color2 color, double angle)
{
	double power;

	power = pow(ft_clamp(angle, 0, 1), 150);
	c.r += power * color.r;
	c.g += power * color.g;
	c.b += power * color.b;
	c.r = ft_clamp(c.r, 0, 255);
	c.g = ft_clamp(c.g, 0, 255);
	c.b = ft_clamp(c.b, 0, 255);
	return (c);
}


t_color2		mult_color(t_color2 c, double coef)
{
	c.r = c.r * coef;
	c.g = c.g * coef;
	c.b = c.b * coef;
	return (c);
}

void		add_branch(t_three *n_branch, t_vector p_hit, double coef, t_color2 c_origin)
{

	n_branch->p_hit = p_hit;
	n_branch->p_hit.coef = coef;
	n_branch->c_origin = c_origin;
}

t_vector	return_v_norm(int type, t_obj obj, t_vector p_hit)
{
	static t_vector (*angle[6])(t_obj, t_vector) = {ft_angle_sphere, ft_angle_plane, ft_angle_cylinder, ft_angle_cone, ft_angle_circle, ft_angle_square};

	return (angle[type - 1](obj, p_hit));
}

int			search_obj(t_parse_obj **list_obj, t_obj obj)
{
	t_parse_obj *begin;
	t_parse_obj *tmp;

	tmp = NULL;
	begin = *list_obj;
	while (begin)
	{
		if ((obj.group == 0 && obj.id == begin->obj.id) || (obj.group != 0 && obj.group == begin->obj.group))
		{
			if (tmp)
				tmp->next = begin->next;
			else
			{
				tmp = begin->next;
				*list_obj = tmp;
			}
			free(begin);
			return (0);
		}
		tmp = begin;
		begin = begin->next;
	}
	return (1);
}

void 		ft_debug(t_parse_obj *obj_list)
{
	printf("ft_debug --------- \n");
	t_parse_obj *begin;
	int 		i = 0;

	begin = obj_list;
	while (obj_list != NULL && obj_list->next != NULL)
	{
		printf("ft_debug --------- id =%d\n", obj_list->obj.id);
		printf("ft_debug -------- i = %d\n", i);
		i++;
		obj_list = obj_list->next;
	}
	obj_list = begin;

}

t_parse_obj	*get_obj_list(t_env *e, t_three *current, t_three *branch)
{
	t_parse_obj	*tmp;
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
		// current->id == 0 || current->id == 1 || current->id == 7 ? printf("current->id = %d, i = %d\n", current->id, i) : 0;
		if (current->id < 0)
			obj = e->l_obj[-current->id - 1];
		else
			obj = e->l_obj[current->id - 1];
		search = search_obj(&rez, obj);
		if (search == 1 && obj.type != 2 && obj.type != 6 && obj.type != 5)
		{
			// i == 2 ? printf("je malloc et il y a une suite\n") : 0;
			tmp = malloc(sizeof(t_parse_obj));
			if (current->id < 0)
				tmp->obj = e->l_obj[-current->id - 1];
			else
				tmp->obj = e->l_obj[current->id - 1];
			tmp->next = rez;
			rez = tmp;
		}
		current = current->r_refrac;
		while (branch != current && !current->r_refrac)
			current = current->r_reflec;
	}
	return (rez);
}

int		ft_get_obj_neg(t_obj obj, t_parse_obj *list_obj, t_three **three, int *id, t_env *e)
{
	(void)three;
	(void)id;
	(void)e;
	(void)list_obj;
	(void)obj;

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
	// else if (obj.negatif == 1)
	// {
	// 	while (list_obj)
	// 	{
	// 		if (list_obj->obj.id == 0)
	// 			printf("Il y a un probleme\n");
	// 		if (list_obj->obj.negatif == 0)
	// 		{
	// 			*id = list_obj->obj.id;
	// 			return (*id);
	// 		}
	// 		list_obj = list_obj->next;
	// 	}
	// }
	return (obj.id - 1);
}


void		ft_raytracer(t_env *e, t_vector p_ray, t_vector v_ray, int prof, double coef, t_color2 c_origin, t_three **three)
{
	t_vector 		p_hit;
	t_vector		v_refrac;
	t_vector		v_reflec;
	t_vector		v_norm;
	int				id;
	int				ret;
	double			dist;
	t_parse_obj		*obj_list;

	dist = inter_obj(e, p_ray, v_ray, &id);
	if (coef < 0.039 || dist < 0.00001 || prof == 20)
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
	(*three)->id = id + 1;
	// printf("id = %d\n", id);
	obj_list = get_obj_list(e, *(e->begin_three), *three);
	ret = ft_get_obj_neg(e->l_obj[id], obj_list, three, &id, e);
	if (ret == -1)
	{
		// printf("id = %d\n", (*three)->id);
		(*three)->id *= -1;
		ft_raytracer(e, p_hit, v_ray, prof, coef, c_origin, &((*three)->r_refrac));
		add_branch(*three, p_hit, coef, c_origin);
		// free(*three);
		// ft_raytracer(e, p_hit, v_ray, prof, coef, c_origin, three);
	}
	else
	{
		if (coef * (1 - e->l_obj[id].ind_transp) * (1 - e->l_obj[id].ind_reflec) > 0.039)
			(*(e->nb_obj_pix))[e->start]++;
		if (e->l_obj[id].ind_reflec > 0)
		{
			v_reflec = get_reflec(v_norm, v_ray);
			ft_raytracer(e, p_hit, v_reflec, prof + 1, coef * e->l_obj[id].ind_reflec, c_origin, &((*three)->r_reflec));
		}
		if (e->l_obj[id].ind_transp > 0)
		{
			c_origin.r = e->l_obj[id].color.r * c_origin.r / 255.0;
			c_origin.g = e->l_obj[id].color.g * c_origin.g / 255.0;
			c_origin.b = e->l_obj[id].color.b * c_origin.b / 255.0;
			v_refrac = (e->l_obj[ret].type != 2 && e->l_obj[ret].type != 6 && e->l_obj[ret].type != 5) ? get_refrac(e, v_norm, v_ray, e->l_obj[ret].ind_refrac) : v_ray;
			ft_raytracer(e, p_hit, v_refrac, prof + 1, coef * e->l_obj[id].ind_transp * (1 - e->l_obj[id].ind_reflec), c_origin, &((*three)->r_refrac));
		}
		add_branch(*three, p_hit, coef, c_origin);
	}
}
