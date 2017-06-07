/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:31:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/07 12:27:41 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			parse_json2(char *line, t_env *e, int *x, char *rez)
{
	if (ft_strcmp(rez, "camera") == 0)
		get_camera(line, x, e);
	else if (ft_strcmp(rez, "light") == 0)
		get_light(line, x, e);
	else if (ft_strcmp(rez, "ambient") == 0)
		get_ambient(line, x, e);
	else if (ft_strcmp(rez, "sphere") == 0 || ft_strcmp(rez, "cone") == 0
		|| ft_strcmp(rez, "cylinder") == 0 || ft_strcmp(rez, "plane") == 0)
		get_object(line, x, e, rez);
	else if (ft_strcmp(rez, "image size") == 0)
		get_image_size(line, x, e);
	else
		ft_error(OBJ_I, "parse_json");
}

void			ft_parse_json(char *line, t_env *e)
{
	int		x;
	char	*rez;

	x = 0;
	line[x] != '{' ? ft_error(J_SON, "parse_json") : x++;
	free_space(line, &x);
	while (line[x] && line[x] != '}')
	{
		free_space(line, &x);
		get_string(line, &x, &rez);
		free_space(line, &x);
		line[x] != ':' ? ft_error(J_SON, "parse_json") : (x++);
		free_space(line, &x);
		parse_json2(line, e, &x, rez);
		free_space(line, &x);
		if (line[x] != ',')
			break ;
		else
			x++;
		free_space(line, &x);
	}
	line[x] != '}' ? ft_error(J_SON, "parse_json") : x++;
}
