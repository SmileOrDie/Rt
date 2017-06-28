/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:36:30 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 19:42:18 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

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

void			add_branch(t_three *n_branch, t_vector p_hit, double coef, \
	t_color2 c_origin)
{
	n_branch->p_hit = p_hit;
	n_branch->p_hit.coef = coef;
	n_branch->c_origin = c_origin;
}

t_vector		return_v_norm(int type, t_obj obj, t_vector p_hit)
{
	static t_vector (*angle[6])(t_obj, t_vector) = {ft_angle_sphere, \
		ft_angle_plane, ft_angle_cylinder, ft_angle_cone, ft_angle_circle, \
		ft_angle_square};

	return (angle[type - 1](obj, p_hit));
}

int				search_obj(t_parse_obj **list_obj, t_obj obj)
{
	t_parse_obj *begin;
	t_parse_obj *tmp;

	tmp = NULL;
	begin = *list_obj;
	while (begin)
	{
		if (obj.id == (*list_obj)->obj.id || (obj.group != 0 && obj.group == \
			(*list_obj)->obj.group))
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
		begin = begin->next;
	}
	return (1);
}
