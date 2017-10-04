/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 20:06:29 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/30 13:40:48 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

int		get_texture_2(t_envg *e, int y, char *path)
{
	while (e->path_tex && (e->path_tex)[y] != NULL)
	{
		if (ft_strcmp(path, (e->path_tex)[y]) == 0)
		{
			free(path);
			e->parse_obj->obj.id_texture = y + 1;
			break ;
		}
		y++;
	}
	return (y);
}

void	add_obj22_2(t_envg *e, int *x, int y, char *line)
{
	int	tmp;

	tmp = 0;
	y = *x;
	if ((tmp = get_number(line, x)) && tmp == 1)
		e->parse_obj->obj.negatif = ft_clamp(ft_atoi(line + y), 0, 1);
}

void	add_obj23_2(t_envg *e, int *x, int y, char *line)
{
	int	tmp;

	tmp = 0;
	if ((tmp = get_number(line, x)))
		e->parse_obj->obj.angle = ft_for_atof(line, y, *x);
	else
		ft_error(N_NUM, "add_obj23");
}

int		add_obj2_2(t_envg *e, int group, char *line, int *x)
{
	free_space(line, x);
	if (e->parse_obj->obj.type == 4 && e->parse_obj->obj.radius != 0)
	{
		e->parse_obj->obj.type = 8;
		e->parse_obj->obj.group = group;
		group++;
	}
	if (e->parse_obj->obj.type == 3 && e->parse_obj->obj.angle != 0)
	{
		e->parse_obj->obj.type = 9;
		e->parse_obj->obj.group = group;
		group++;
	}
	e->group_max = group;
	e->e->group_max = group;
	return (group);
}

void	add_obj2_3(t_envg *e, char *line, int *x, char *rez)
{
	free_space(line, x);
	add_obj23(line, x, e, rez);
	add_obj24(line, x, e, rez);
	free_space(line, x);
	free(rez);
}
