/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:27:58 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/07 12:07:52 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_obj	g_default_object = {2, -1, 50, 0, 0, {0, 0, 0, 0}, {0, 0, 0, 0},
	{0, 0, 0, 0}, 60, NULL, 0, {255, 255, 255, 255}};
t_light	g_default_light = {{0, 0, 0, 0}, {255, 255, 255, 255}, 0, 0, NULL};

void			increase_l_obj(t_env *e)
{
	t_parse_obj	*tmp;

	tmp = malloc(sizeof(t_parse_obj));
	tmp->next = e->parse_obj;
	e->parse_obj = tmp;
}

int				get_object(char *line, int *x, t_env *e, char *name)
{
	increase_l_obj(e);
	e->parse_obj->obj = g_default_object;
	line[*x] != '{' ? ft_error(J_SON, "get_object") : (*x)++;
	if (ft_strcmp(name, "sphere") == 0)
		add_obj2(line, x, e, 1);
	else if (ft_strcmp(name, "cone") == 0)
		add_obj2(line, x, e, 3);
	else if (ft_strcmp(name, "cylinder") == 0)
		add_obj2(line, x, e, 4);
	else if (ft_strcmp(name, "plane") == 0)
		add_obj2(line, x, e, 2);
	else
		ft_error(OBJ_I, "get_object");
	line[*x] != '}' ? ft_error(J_SON, "get_object") : (*x)++;
	return (1);
}

void			increase_light(t_env *e)
{
	t_parse_light *tmp;

	tmp = malloc(sizeof(t_parse_light));
	tmp->next = e->parse_light;
	e->parse_light = tmp;
}

void			get_light2(char *line, int *x, t_env *e, char *name)
{
	if (ft_strcmp(name, "color") == 0)
		e->parse_light->light.color = get_t_color(line, x);
	if (ft_strcmp(name, "pos") == 0)
		e->parse_light->light.pos = get_t_vector(line, x);
	if (ft_strcmp(name, "name") == 0)
		get_string(line, x, &(e->parse_light->light.name));
}

void			get_light(char *line, int *x, t_env *e)
{
	char	*name;

	increase_light(e);
	e->parse_light->light = g_default_light;
	line[*x] != '{' ? ft_error(J_SON, "get_light") : (*x)++;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &name);
		free_space(line, x);
		line[*x] != ':' ?
			ft_error(J_SON, "get_light") : ((*x)++);
		free_space(line, x);
		get_light2(line, x, e, name);
		free_space(line, x);
		if (line[*x] != ',')
			break ;
		else
			(*x)++;
		free_space(line, x);
	}
	free_space(line, x);
	line[*x] != '}' ? ft_error(J_SON, "get_light") : (*x)++;
}
