/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:41:31 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 12:07:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static t_vector	matricemult(double m2[3][3], t_vector p)
{
	double rez[3];

	rez[0] = p.x * m2[0][0] + p.y * m2[0][1] + p.z * m2[0][2];
	rez[1] = p.x * m2[1][0] + p.y * m2[1][1] + p.z * m2[1][2];
	rez[2] = p.x * m2[2][0] + p.y * m2[2][1] + p.z * m2[2][2];
	p.x = rez[0];
	p.y = rez[1];
	p.z = rez[2];
	return (p);
}

static void	init_z(double (*m2)[3][3], char axe, double theta)
{
	if (axe == 'z')
	{
		(*m2)[0][0] = cos(theta);
		(*m2)[0][1] = -1 * sin(theta);
		(*m2)[0][2] = 0;
		(*m2)[1][0] = sin(theta);
		(*m2)[1][1] = cos(theta);
		(*m2)[1][2] = 0;
		(*m2)[2][0] = 0;
		(*m2)[2][1] = 0;
		(*m2)[2][2] = 1;
	}
}

static void	init_y(double (*m2)[3][3], char axe, double theta)
{
	if (axe == 'y')
	{
		(*m2)[0][0] = cos(theta);
		(*m2)[0][1] = 0;
		(*m2)[0][2] = sin(theta);
		(*m2)[1][0] = 0;
		(*m2)[1][1] = 1;
		(*m2)[1][2] = 0;
		(*m2)[2][0] = -1 * sin(theta);
		(*m2)[2][1] = 0;
		(*m2)[2][2] = cos(theta);
	}
}

static void	init_x(double (*m2)[3][3], char axe, double theta)
{
	if (axe == 'x')
	{
		(*m2)[0][0] = 1;
		(*m2)[0][1] = 0;
		(*m2)[0][2] = 0;
		(*m2)[1][0] = 0;
		(*m2)[1][1] = cos(theta);
		(*m2)[1][2] = -1 * sin(theta);
		(*m2)[2][0] = 0;
		(*m2)[2][1] = sin(theta);
		(*m2)[2][2] = cos(theta);
	}
}

t_vector	mult_mat(char axe, double theta, t_vector point)
{
	int		p;
	double	m2[3][3];

	p = 0;
	init_z(&m2, axe, theta);
	init_y(&m2, axe, theta);
	init_x(&m2, axe, theta);
	point = matricemult(m2, point);
	return (point);
}

void	get_matrice(t_vector dir, t_vector **mat)
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

void			get_obj_lst(t_envg *e, t_obj obj, int *i)
{
	int			nb;
	t_vector	*mat;

	nb = 0;
	if (obj.type == 7)
	{
		mat = malloc(sizeof(t_vector) * 3);
		get_matrice(obj.dir, &mat);
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[0];
		e->e->l_obj[*i].point = mat[1];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[0], obj.radius / 2));
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[0];
		e->e->l_obj[*i].point = mat[1];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[0],  -obj.radius / 2));
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[1];
		e->e->l_obj[*i].point = mat[2];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[1], obj.radius / 2));
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[1];
		e->e->l_obj[*i].point = mat[2];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[1],  -obj.radius / 2));
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[2];
		e->e->l_obj[*i].point = mat[0];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[2], obj.radius / 2));
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 6;
		e->e->l_obj[*i].dir = mat[2];
		e->e->l_obj[*i].point = mat[0];
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(mat[2],  -obj.radius / 2));
	}
	if (obj.type == 8)
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
	if (obj.type == 9)
	{
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].id = *i + 1;
		e->e->l_obj[*i].type = 3;
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].type = 5;
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(obj.dir, -obj.angle / 2.0));
		e->e->l_obj[*i].id = *i + 1;
		(*i)++;
		e->e->l_obj[*i] = obj;
		e->e->l_obj[*i].type = 5;
		e->e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(obj.dir, obj.angle / 2.0));
		e->e->l_obj[*i].dir = vmult_dbl(obj.dir, -1);
		e->e->l_obj[*i].id = *i + 1;
	}
}

void			ft_creat_lst_obj(t_envg *e)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;
	int 				i;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7)
			i += 5;
		else if (parse_obj_b->obj.type == 8)
			i++;
		else if (parse_obj_b->obj.type == 9)
			i += 2;
		parse_obj_b = parse_obj_b->next;
		i++;
	}
	e->e->nb_obj = i;
	i = 0;
	while (parse_light_b)
	{
		parse_light_b = parse_light_b->next;
		i++;
	}
	e->e->nb_light = i;
	if (!(e->e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->e->nb_obj)))
		ft_error(MALLOC, "e->e->l_obj -> rt.h");
	if (!(e->e->light = (t_light *)malloc(sizeof(t_light) * e->e->nb_light)))
		ft_error(MALLOC, "e->e->light -> rt.h");
	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7 || parse_obj_b->obj.type == 8 ||
			parse_obj_b->obj.type == 9)
			get_obj_lst(e, parse_obj_b->obj, &i);
		else
		{
			e->e->l_obj[i] = parse_obj_b->obj;
			e->e->l_obj[i].id = i + 1;
		}
		i++;
		parse_obj_b = parse_obj_b->next;
	}
	i = 0;
	while (parse_light_b)
	{
		e->e->light[i] = parse_light_b->light;
		parse_light_b = parse_light_b->next;
		i++;
	}
}