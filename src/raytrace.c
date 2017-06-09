/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/07 14:51:35 by pde-maul         ###   ########.fr       */
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
			*id = e->l_obj[i].id;
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

void		add_branch(t_three **n_branch, int id, t_vector p_hit, double coef, t_color2 c_origin)
{

	(*n_branch)->id = id;
	(*n_branch)->p_hit = p_hit;
	(*n_branch)->p_hit.coef = coef;
	(*n_branch)->c_origin = c_origin;
}

t_vector	return_v_norm(int type, t_obj obj, t_vector p_hit)
{
	static t_vector (*angle[6])(t_obj, t_vector) = {ft_angle_sphere, ft_angle_plane, ft_angle_cylinder, ft_angle_cone, ft_angle_circle, ft_angle_square};

	return (angle[type - 1](obj, p_hit));
}

void		ft_raytracer(t_env *e, t_color2 pixel, t_vector p_ray, t_vector v_ray, int prof, double coef, t_color2 c_origin, t_three **three)
{
	t_vector 		p_hit;
	t_vector		v_refrac;
	t_vector		v_reflec;
	t_vector		v_norm;
	int				id;
	double			dist;

	dist = inter_obj(e, p_ray, v_ray, &id);
	if (coef < 0.0039 || dist == -1 || prof == 20)
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
	if (e->l_obj[id].ind_reflec > 0)
	{
		v_reflec = get_reflec(v_norm, v_ray);
		ft_raytracer(e, pixel, p_hit, v_reflec, prof + 1, coef * e->l_obj[id].ind_reflec, c_origin, &((*three)->r_reflec));
	}
	if (e->l_obj[id].ind_transp > 0)
	{
		v_refrac = get_refrac(e, v_norm, v_ray, e->l_obj[id].ind_refrac);
		c_origin.r = (e->l_obj[id].color.r * c_origin.r / -255.0 + c_origin.r);
		c_origin.g = (e->l_obj[id].color.g * c_origin.g / -255.0 + c_origin.g);
		c_origin.b = (e->l_obj[id].color.b * c_origin.b / -255.0 + c_origin.b);
		ft_raytracer(e, pixel, p_hit, v_refrac, prof + 1, coef * e->l_obj[id].ind_transp * (1 - e->l_obj[id].ind_reflec), c_origin, &((*three)->r_refrac));
	}
	// color_light = add_light(e, (t_color2){0, 0, 0, 0}, p_hit, e->l_obj[id]);
	// color_ray = mult_color2(color_light, coef * (1 - e->l_obj[id].ind_transp) * (1 - e->l_obj[id].ind_reflec));
	// pixel = add_color(pixel, color_ray);
	if (coef * (1 - e->l_obj[id].ind_transp) * (1 - e->l_obj[id].ind_reflec) > 0.039)
		(*(e->nb_obj_pix))[e->start]++;
	add_branch(three, e->l_obj[id].id, p_hit, coef, c_origin);
}
