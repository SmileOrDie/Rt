/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create_env_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:41:31 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/24 18:30:36 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		get_matrice(t_vector dir, t_vector **mat)
{
	t_vector mat_x;
	t_vector mat_y;
	t_vector mat_z;

	mat_x = mult_mat('x', dir.x * M_PI / 2, (t_vector){1, 0, 0, 0});
	mat_x = mult_mat('y', dir.y * M_PI / 2, mat_x);
	mat_x = mult_mat('z', dir.z * M_PI / 2, mat_x);
	mat_y = mult_mat('x', dir.x * M_PI / 2, (t_vector){0, 1, 0, 0});
	mat_y = mult_mat('y', dir.y * M_PI / 2, mat_y);
	mat_y = mult_mat('z', dir.z * M_PI / 2, mat_y);
	mat_z = mult_mat('x', dir.x * M_PI / 2, (t_vector){0, 0, 1, 0});
	mat_z = mult_mat('y', dir.y * M_PI / 2, mat_z);
	mat_z = mult_mat('z', dir.z * M_PI / 2, mat_z);
	(*mat)[0] = mat_x;
	(*mat)[1] = mat_y;
	(*mat)[2] = mat_z;
}

static void		cal_mat(t_envg *e, t_obj obj, t_vector *mat, double o[4])
{
	e->e->l_obj[(int)o[3]] = obj;
	e->e->l_obj[(int)o[3]].id = ((int)o[3]) + 1;
	e->e->l_obj[(int)o[3]].type = 6;
	e->e->l_obj[(int)o[3]].dir = mat[(int)o[0]];
	e->e->l_obj[(int)o[3]].point = mat[(int)o[1]];
	e->e->l_obj[(int)o[3]].pos = vadd(obj.pos, vmult_dbl(mat[(int)o[0]],
		(o[2] * obj.radius)));
}

static void		get_obj_lst_1(t_envg *e, t_obj obj, int *i)
{
	t_vector	*mat;

	if (obj.type == 7)
	{
		mat = malloc(sizeof(t_vector) * 3);
		get_matrice(obj.dir, &mat);
		cal_mat(e, obj, mat, (double[4]){0, 1, 0.5, (*i)++});
		cal_mat(e, obj, mat, (double[4]){0, 1, -0.5, (*i)++});
		cal_mat(e, obj, mat, (double[4]){1, 2, 0.5, (*i)++});
		cal_mat(e, obj, mat, (double[4]){1, 2, -0.5, (*i)++});
		cal_mat(e, obj, mat, (double[4]){2, 0, 0.5, (*i)++});
		cal_mat(e, obj, mat, (double[4]){2, 0, -0.5, *i});
	}
	else if (obj.type == 8)
	{
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 4;
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].type = 5;
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(obj.dir, -obj.radius));
		e->e->l_obj[*i].radius = tan(obj.angle / 360.0 * M_PI) * obj.radius;
		e->e->l_obj[*i].id = *i + 1;
	}
}

void			get_obj_lst(t_envg *e, t_obj obj, int *i)
{
	if (obj.type == 9)
	{
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 3;
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].type = 5;
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(obj.dir, -obj.angle));
		e->e->l_obj[*i].id = *i + 1;
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].type = 5;
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(obj.dir, obj.angle));
		e->e->l_obj[*i].id = *i + 1;
	}
	else
		get_obj_lst_1(e, obj, i);
}
