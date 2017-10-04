/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:27:58 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/16 20:03:37 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_obj	g_default_object = {0, 0, 0, 0, {0, 0, 0, 0}, {1, 0, 0, 0},
	{0, 0, 0, 0}, 0, 0, 0, 0, NULL, {255, 255, 255, 255}, 0, 0, 0};
t_light	g_default_light = {{0, 0, 0, 0}, {255, 255, 255, 255}, 0, 0, NULL};

void			increase_l_obj(t_envg *e)
{
	t_parse_obj	*tmp;

	tmp = malloc(sizeof(t_parse_obj));
	tmp->next = e->parse_obj;
	e->parse_obj = tmp;
}

int				get_object(char *line, int *x, t_envg *e, char *name)
{
	increase_l_obj(e);
	e->parse_obj->obj = g_default_object;
	e->parse_obj->obj.name = ft_strdup(name);
	line[*x] != '{' ? ft_error(J_SON, "get_object") : (*x)++;
	if (ft_strcmp(name, "sphere") == 0)
		add_obj2(line, x, e, 1);
	else if (ft_strcmp(name, "cone") == 0)
		add_obj2(line, x, e, 4);
	else if (ft_strcmp(name, "cylinder") == 0)
		add_obj2(line, x, e, 3);
	else if (ft_strcmp(name, "plane") == 0)
		add_obj2(line, x, e, 2);
	else if (ft_strcmp(name, "circle") == 0)
		add_obj2(line, x, e, 5);
	else if (ft_strcmp(name, "square") == 0)
		add_obj2(line, x, e, 6);
	else if (ft_strcmp(name, "cube") == 0)
		add_obj2(line, x, e, 7);
	else
		ft_error(OBJ_I, "get_object");
	line[*x] != '}' ? ft_error(J_SON, "get_object") : (*x)++;
	return (1);
}

void			increase_light(t_envg *e)
{
	t_parse_light *tmp;

	tmp = malloc(sizeof(t_parse_light));
	tmp->next = e->parse_light;
	e->parse_light = tmp;
}

void			get_light2(char *line, int *x, t_envg *e, char *name)
{
	if (ft_strcmp(name, "color") == 0)
		e->parse_light->light.color = get_t_color(line, x);
	if (ft_strcmp(name, "pos") == 0)
		e->parse_light->light.pos = get_t_vector(line, x, 0);
	if (ft_strcmp(name, "name") == 0)
	{
		free(e->parse_light->light.name);
		get_string(line, x, &(e->parse_light->light.name));
	}
}

void			get_light(char *line, int *x, t_envg *e)
{
	char	*name;

	increase_light(e);
	e->parse_light->light = g_default_light;
	e->parse_light->light.name = ft_strdup("light");
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
		free(name);
		if (line[*x] != ',')
			break ;
		else
			(*x)++;
		free_space(line, x);
	}
	free_space(line, x);
	line[*x] != '}' ? ft_error(J_SON, "get_light") : (*x)++;
}
