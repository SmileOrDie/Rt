/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:35:01 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/13 19:27:38 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void	get_texture(char *line, int *x, t_env *e)
{
	char	*path;
	char	**new;
	int		y;

	y = 0;
	get_string(line, x, &path);
	while ((e->path_tex)[y] != NULL)
	{
		if (ft_strcmp(path, (e->path_tex)[y]) == 0)
		{
			e->parse_obj->obj.id_texture = y + 1;
			break ;
		}
		y++;
	}
	if ((e->path_tex)[y] == NULL)
	{
		new = malloc(sizeof(char*) * (y + 2));
		y = 0;
		while ((e->path_tex)[y] != NULL)
		{
			new[y] = (e->path_tex)[y];
			y++;
		}
		new[y] = path;
		new[y + 1] = NULL;
		free(e->path_tex);
		e->path_tex = new;
		e->parse_obj->obj.id_texture = y + 1;
	}
}

void	add_obj22(char *line, int *x, t_env *e, char *rez)
{
	int y;
	int tmp;

	if (ft_strcmp(rez, "radius") == 0 && ((y = *x) || 1))
	{
		if (((tmp = get_number(line, x)) || 1) && tmp != 0)
			e->parse_obj->obj.radius = ft_clamp_min(
				ft_for_atof(line, y, *x), 0);
		else
			ft_error(N_NUM, "add_obj22");
	}
	else if (ft_strcmp(rez, "ind_refrac") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x) || 1) && tmp != 0)
			e->parse_obj->obj.ind_refrac = ft_clamp(
				ft_for_atof(line, y, *x), 0, 3);
		else
			ft_error(N_NUM, "add_obj22");
	}
	else if (ft_strcmp(rez, "texture") == 0)
		get_texture(line, x, e);
	else if (ft_strcmp(rez, "negatif") == 0)
	{
		y = *x;
		if ((tmp = get_number(line, x)) && tmp == 1)
			e->parse_obj->obj.negatif = ft_clamp(ft_atoi(line + y), 0, 1);
	}
}

void	add_obj23(char *line, int *x, t_env *e, char *rez)
{
	int y;
	int tmp;

	if (ft_strcmp(rez, "name") == 0)
	{
		free(e->parse_obj->obj.name);
		get_string(line, x, &(e->parse_obj->obj.name));
	}
	add_obj22(line, x, e, rez);
	if (ft_strcmp(rez, "ind_reflec") == 0 && ((y = *x) || 1))
		if ((tmp = get_number(line, x)))
			e->parse_obj->obj.ind_reflec = ft_clamp(
				ft_for_atof(line, y, *x), 0, 1);
		else
			ft_error(OBJ_I, "add_obj23");
	else if (ft_strcmp(rez, "ind_transp") == 0 && ((y = *x) || 1))
		if ((tmp = get_number(line, x)))
			e->parse_obj->obj.ind_transp = ft_clamp(
				ft_for_atof(line, y, *x), 0, 1);
		else
			ft_error(N_NUM, "add_obj23");
	else if (ft_strcmp(rez, "angle") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			e->parse_obj->obj.angle = ft_for_atof(line, y, *x);
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

void	add_obj2(char *line, int *x, t_env *e, int type)
{
	static int	id = 0;
	static int	group = 1;
	char		*rez;


	e->parse_obj->obj.id = id;
	e->parse_obj->obj.type = type;
	e->parse_obj->obj.group = (type == 7) ? group : 0;
	type == 7 ? group++ : 0;
	e->group_max = group;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &rez);
		free_space(line, x);
		line[*x] != ':' ? ft_error(J_SON, "add_obj2") : ((*x)++);
		free_space(line, x);
		add_obj23(line, x, e, rez);
		add_obj24(line, x, e, rez);
		free_space(line, x);
		free(rez);
		if (line[*x] != ',')
			break ;
		line[*x] == ',' ? (*x)++ : 0;
		free_space(line, x);
	}
	free_space(line, x);
	id++;
}
