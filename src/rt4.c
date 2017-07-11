/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 10:57:37 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/10 17:30:53 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			ft_creat_lst_obj3(t_env *e, t_norme10 n)
{
	while (n.parse_light_b)
	{
		e->light[n.i] = n.parse_light_b->light;
		n.parse_light_b = n.parse_light_b->next;
		n.i++;
	}
}

void			ft_creat_lst_obj2(t_env *e, t_norme10 n)
{
	e->nb_light = n.i;
	if (!(e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->nb_obj)))
		ft_error(MALLOC, "e->l_obj -> rt.h");
	if (!(e->light = (t_light *)malloc(sizeof(t_light) * e->nb_light)))
		ft_error(MALLOC, "e->light -> rt.h");
	n.parse_obj_b = e->parse_obj;
	n.parse_light_b = e->parse_light;
	n.i = 0;
	while (n.parse_obj_b)
	{
		if (n.parse_obj_b->obj.type == 7 || n.parse_obj_b->obj.type == 8 ||
			n.parse_obj_b->obj.type == 9)
			get_obj_lst(e, n.parse_obj_b->obj, &n.i);
		else
		{
			e->l_obj[n.i] = n.parse_obj_b->obj;
			e->l_obj[n.i].id = n.i;
		}
		n.i++;
		n.parse_obj_b = n.parse_obj_b->next;
	}
	n.i = 0;
	ft_creat_lst_obj3(e, n);
}

void			ft_creat_lst_obj(t_env *e)
{
	t_norme10	n;

	n.parse_obj_b = e->parse_obj;
	n.parse_light_b = e->parse_light;
	n.i = 0;
	while (n.parse_obj_b)
	{
		if (n.parse_obj_b->obj.type == 7)
			n.i += 2;
		else if (n.parse_obj_b->obj.type == 8)
			n.i++;
		else if (n.parse_obj_b->obj.type == 9)
			n.i += 2;
		n.parse_obj_b = n.parse_obj_b->next;
		n.i++;
	}
	e->nb_obj = n.i;
	n.i = 0;
	while (n.parse_light_b)
	{
		n.parse_light_b = n.parse_light_b->next;
		n.i++;
	}
	ft_creat_lst_obj2(e, n);
}

void			get_l_tab(t_env *e)
{
	int		i;
	char	flag;

	i = 0;
	flag = 2;
	while (i < e->mlx->h * e->mlx->w)
	{
		e->coef_t[i] = get_l_pix(e->tab_three[i], e->tab_light, e->l_obj, flag);
		i++;
		flag = 1;
	}
}

void			get_matrice(t_vector dir, t_vector **mat)
{
	t_vector mat_x;
	t_vector mat_y;
	t_vector mat_z;

	vnorm(&dir);
	mat_x.x = 1;
	mat_x.y = 0;
	mat_x.z = 0;
	mat_y.x = 0;
	mat_y.y = 1;
	mat_y.z = 0;
	mat_z.x = 0;
	mat_z.y = 0;
	mat_z.z = 1;
	mat_x = vrot(vcross(dir, (t_vector){1, 0, 0, 0}), acos(vpscal(dir, \
		(t_vector){1, 0, 0, 0})) / M_PI * 180, mat_x);
	mat_y = vrot(vcross(dir, (t_vector){0, 1, 0, 0}), acos(vpscal(dir, \
		(t_vector){0, 1, 0, 0})) / M_PI * 180, mat_y);
	mat_z = vrot(vcross(dir, (t_vector){0, 0, 1, 0}), acos(vpscal(dir, \
		(t_vector){0, 0, 1, 0})) / M_PI * 180, mat_z);
	(*mat)[0] = mat_x;
	(*mat)[1] = mat_y;
	(*mat)[2] = mat_z;
}
