/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:10:24 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/02 14:26:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		get_t_vector2(char *line, int *x, char *name, t_vector *rez)
{
	int			y;
	int			tmp;

	if (ft_strcmp(name, "x") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->x = ft_for_atof(line, y, *x);
		else
			ft_error(N_NUM, "get_t_vector2");
	}
	else if (ft_strcmp(name, "y") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->y = ft_for_atof(line, y, *x);
		else
			ft_error(N_NUM, "get_t_vector2");
	}
	else if (ft_strcmp(name, "z") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->z = ft_for_atof(line, y, *x);
		else
			ft_error(N_NUM, "get_t_vector2");
	}
	free_space(line, x);
}

t_vector	get_t_vector(char *line, int *x, int norme)
{
	t_vector	rez;
	char		*name;

	line[*x] != '{' ? ft_error(J_SON, "get_t_vector") : (*x)++;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &name);
		free_space(line, x);
		line[*x] != ':' ?
			ft_error(J_SON, "get_t_vector") : ((*x)++);
		free_space(line, x);
		get_t_vector2(line, x, name, &rez);
		free(name);
		if (line[*x] != ',')
			break ;
		else
			(*x)++;
		free_space(line, x);
	}
	free_space(line, x);
	line[*x] != '}' ? ft_error(J_SON, "get_t_vector") : (*x)++;
	norme ? vnorm(&rez) : 0;
	rez.coef = 0;
	return (rez);
}
