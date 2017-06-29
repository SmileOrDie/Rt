/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:35:01 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 18:05:06 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void	add_obj23_1(t_env *e, char *line, int *x)
{
	free(e->parse_obj->obj.name);
	get_string(line, x, &(e->parse_obj->obj.name));
}

void	add_obj23(char *line, int *x, t_env *e, char *rez)
{
	t_norme8	n;

	if (ft_strcmp(rez, "name") == 0)
		add_obj23_1(e, line, x);
	add_obj22(line, x, e, rez);
	if (ft_strcmp(rez, "ind_reflec") == 0 && ((n.y = *x) || 1))
		if ((n.tmp = get_number(line, x)))
			e->parse_obj->obj.ind_reflec = ft_clamp(
				ft_for_atof(line, n.y, *x), 0, 1);
		else
			ft_error(OBJ_I, "add_obj23");
	else if (ft_strcmp(rez, "ind_transp") == 0 && ((n.y = *x) || 1))
		if ((n.tmp = get_number(line, x)))
			e->parse_obj->obj.ind_transp = ft_clamp(
				ft_for_atof(line, n.y, *x), 0, 1);
		else
			ft_error(N_NUM, "add_obj23");
	else if (ft_strcmp(rez, "angle") == 0 && ((n.y = *x) || 1))
	{
		if ((n.tmp = get_number(line, x)))
			e->parse_obj->obj.angle = ft_for_atof(line, n.y, *x);
		else
			ft_error(N_NUM, "add_obj23");
	}
}

void	add_obj24(char *line, int *x, t_env *e, char *rez)
{
	if (ft_strcmp(rez, "color") == 0)
		e->parse_obj->obj.color = get_t_color(line, x);
	else if (ft_strcmp(rez, "pos") == 0)
		e->parse_obj->obj.pos = get_t_vector(line, x, 0);
	else if (ft_strcmp(rez, "dir") == 0)
		e->parse_obj->obj.dir = get_t_vector(line, x, 1);
}

void	add_obj2_1(char *line, int *x, t_env *e, t_norme4 n)
{
	get_string(line, x, &n.rez);
	free_space(line, x);
	line[*x] != ':' ? ft_error(J_SON, "add_obj2") : ((*x)++);
	free_space(line, x);
	add_obj23(line, x, e, n.rez);
	add_obj24(line, x, e, n.rez);
	free_space(line, x);
	free(n.rez);
}

void	add_obj2(char *line, int *x, t_env *e, int type)
{
	t_norme4	n;

	n.id = 0;
	n.group = 1;
	e->parse_obj->obj.id = n.id;
	e->parse_obj->obj.type = type;
	e->parse_obj->obj.group = (type == 7) ? n.group : 0;
	type == 7 ? n.group++ : 0;
	e->group_max = n.group;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		add_obj2_1(line, x, e, n);
		if (line[*x] != ',')
			break ;
		line[*x] == ',' ? (*x)++ : 0;
		free_space(line, x);
	}
	free_space(line, x);
	n.id++;
}
