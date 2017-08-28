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

double		return_dist(t_obj obj, t_vector p_ray, t_vector v_ray)
{
	static double (*inter[6])(t_obj, t_vector, t_vector) = {inter_sphere,
		inter_plane, inter_cylinder, inter_cone, inter_circle, inter_square};

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

t_vector	get_refrac(t_env *e, t_vector v_norm, t_vector v_dir,
	double ind_refrac)
{
	double		c1;
	double		c2;
	t_vector	ret;
	double		n;

	if (e->actual_indice != ind_refrac)
		n = e->actual_indice / ind_refrac;
	else
		n = e->actual_indice / e->default_indice;
	n > 1 ? (n = 1 / n) : 0;
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

t_vector	get_reflec(t_vector v_norm, t_vector v_dir)
{
	double c1;

	c1 = vpscal(v_norm, vmult_dbl(v_dir, -1));
	return (vadd(v_dir, vmult_dbl(v_norm, 2 * c1)));
}

t_color2	add_color(t_color2 c1, t_color2 c2)
{
	t_color2	rez;

	rez.r = c1.r + c2.r;
	rez.g = c1.g + c2.g;
	rez.b = c1.b + c2.b;
	return (rez);
}
