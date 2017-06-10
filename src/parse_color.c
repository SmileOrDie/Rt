/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:17:39 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/07 12:05:55 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		get_t_color2(char *line, int *x, char *name, t_color2 *rez)
{
	int			y;
	int			tmp;

	if (ft_strcmp(name, "r") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->r = ft_atoi(line + y);
		else
			ft_error(N_NUM, "get_t_color2");
	}
	else if (ft_strcmp(name, "g") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->g = ft_atoi(line + y);
		else
			ft_error(N_NUM, "get_t_color2");
	}
	else if (ft_strcmp(name, "b") == 0 && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			rez->b = ft_atoi(line + y);
		else
			ft_error(N_NUM, "get_t_color2");
	}
}

t_color2	get_t_color(char *line, int *x)
{
	t_color2	rez;
	char		*name;

	line[*x] != '{' ? ft_error(J_SON, "get_t_color") : (*x)++;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &name);
		free_space(line, x);
		line[*x] != ':' ?
			ft_error(J_SON, "get_t_color") : ((*x)++);
		free_space(line, x);
		get_t_color2(line, x, name, &rez);
		free_space(line, x);
		free(name);
		if (line[*x] != ',')
			break ;
		else
			(*x)++;
		free_space(line, x);
	}
	free_space(line, x);
	line[*x] != '}' ? ft_error(J_SON, "get_t_color") : (*x)++;
	return (rez);
}
