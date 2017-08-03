/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:23:52 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/02 18:13:54 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			free_space(char *line, int *x)
{
	while (line[*x] && (line[*x] == ' ' || line[*x] == '\n'
		|| line[*x] == '\t'))
		(*x)++;
}

int				get_string(char *line, int *x, char **str)
{
	int	y;
	int	slach;

	slach = 0;
	if (line[*x] != '"')
		ft_error(J_SON, "get_string");
	(*x)++;
	y = *x;
	while (line[y] && (line[y] != '"' || (line[y] == '"'
		&& line[y - 1] == '\\')))
	{
		line[y] == '"' && line[y - 1] == '\\' ? slach++ : 0;
		y++;
	}
	*str = malloc(y + 1 - *x - slach);
	ft_strncpy(*str, line + *x, y - *x - slach);
	*x = y + 1;
	return (1);
}

int				get_number(char *line, int *x)
{
	int double_flag;

	double_flag = 0;
	line[*x] == '-' ? (*x)++ : 0;
	if (line[*x] > '0' && line[*x] <= '9')
	{
		while (line[*x] >= '0' && line[*x] <= '9')
			(*x)++;
	}
	else if (line[*x] != '0')
		return (0);
	else
		(*x)++;
	if (line[*x] == '.')
	{
		double_flag = 1;
		(*x)++;
		if (line[*x] >= '0' && line[*x] <= '9')
			while (line[*x] >= '0' && line[*x] <= '9')
				(*x)++;
		else
			return (0);
	}
	return (double_flag + 1);
}

double			ft_for_atof(char *line, int y, int x)
{
	char	*tmp;
	double	nb;

	tmp = NULL;
	nb = 0;
	tmp = malloc(sizeof(char) * (x - y + 1));
	ft_strncpy(tmp, line + y, x - y);
	nb = ft_atof(tmp);
	free(tmp);
	return (nb);
}

void			get_ambient(char *line, int *x, t_envg *e)
{
	int	y;
	int	tmp;

	y = *x;
	tmp = get_number(line, x);
	if (tmp != 0)
		e->amb = ft_for_atof(line, y, *x);
	else
		ft_error(N_NUM, "get_ambient");
}
