/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:31:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/16 20:04:48 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			parse_json2(char *line, t_envg *e, int *x, char *rez)
{
	int		y;

	if (ft_strcmp(rez, "camera") == 0)
		get_camera(line, x, e);
	else if (ft_strcmp(rez, "light") == 0)
		get_light(line, x, e);
	else if (ft_strcmp(rez, "ambient") == 0)
		get_ambient(line, x, e);
	else if (ft_strcmp(rez, "sphere") == 0 || ft_strcmp(rez, "cone") == 0
		|| ft_strcmp(rez, "cylinder") == 0 || ft_strcmp(rez, "plane") == 0
		|| ft_strcmp(rez, "circle") == 0 || ft_strcmp(rez, "square") == 0
		|| ft_strcmp(rez, "cube") == 0)
		get_object(line, x, e, rez);
	else if (ft_strcmp(rez, "image size") == 0)
		get_image_size(line, x, e);
	else if (ft_strcmp(rez, "anti-aliasing") == 0)
	{
		y = *x;
		if (get_number(line, x) == 1)
			e->anti_a = ft_clamp(ft_atoi(line + y), 1, 4);
		else
			ft_error(N_NUM, "parse_json2");
	}
	else
		ft_error(OBJ_I, "parse_json");
}

void			ft_parse_json(char *line, t_envg *e)
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
		free(rez);
		if (line[x] != ',')
			break ;
		else
			x++;
		free_space(line, &x);
	}
	line[x] != '}' ? ft_error(J_SON, "parse_json") : x++;
}
