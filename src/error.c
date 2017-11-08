/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:42:12 by shamdani          #+#    #+#             */
/*   Updated: 2017/11/08 18:41:20 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			print_obj(t_env *e, int id)
{
	int x;

	x = 0;
	while (e->l_obj[x].id != id && x < e->nb_obj)
		x++;
	// if (e->l_obj[x].id != id)
		printf(
"angle = %f\nradius = %f\nind_refrac = %f\nind_reflec = %f\npos.x = %f %f %f\ndir = %f %f %f\npoint = %f %f %f\nind_transp = %f\ngroup = %d\nnegatif = %d\nvide = %d\nname = %s\ncolor = %d %d %d\nid = %d\ntype = %d\nid_texture = %d\n",
e->l_obj[x].angle,
e->l_obj[x].radius,
e->l_obj[x].ind_refrac,
e->l_obj[x].ind_reflec,
e->l_obj[x].pos.x,
e->l_obj[x].pos.y,
e->l_obj[x].pos.z,
e->l_obj[x].dir.x,
e->l_obj[x].dir.y,
e->l_obj[x].dir.z,
e->l_obj[x].point.x,
e->l_obj[x].point.y,
e->l_obj[x].point.z,
e->l_obj[x].ind_transp,
e->l_obj[x].group,
e->l_obj[x].negatif,
e->l_obj[x].vide,
e->l_obj[x].name,
e->l_obj[x].color.r,
e->l_obj[x].color.g,
e->l_obj[x].color.b,
e->l_obj[x].id,
e->l_obj[x].type,
e->l_obj[x].id_texture);
}

void			ft_error(char *error, char *in)
{
	write(2, error, ft_strlen(error));
	write(2, in, ft_strlen(in));
	write(2, "\n", 1);
	exit(-1);
}

void			ft_error_var(t_vector v, char *str, int f)
{
	if (f == 1)
	{
		if (v.x <= 0 || v.y <= 0 || v.z <= 0)
			ft_error("vector can't be NULL or negatif : ", str);
	}
	else
	{
		if (v.x < 0 || v.y < 0 || v.z < 0)
			ft_error("vector can't be negatif : ", str);
	}
}
