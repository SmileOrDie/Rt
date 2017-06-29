/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 18:04:36 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 18:05:03 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void	get_texture2(t_norme9 n, t_env *e)
{
	n.new[n.y] = n.path;
	n.new[n.y + 1] = NULL;
	free(e->path_tex);
	e->path_tex = n.new;
	e->parse_obj->obj.id_texture = n.y + 1;
}

void	get_texture(char *line, int *x, t_env *e)
{
	t_norme9		n;

	n.y = 0;
	get_string(line, x, &n.path);
	while ((e->path_tex)[n.y] != NULL)
	{
		if (ft_strcmp(n.path, (e->path_tex)[n.y]) == 0)
		{
			e->parse_obj->obj.id_texture = n.y + 1;
			break ;
		}
		n.y++;
	}
	if ((e->path_tex)[n.y] == NULL)
	{
		n.new = malloc(sizeof(char*) * (n.y + 2));
		n.y = 0;
		while ((e->path_tex)[n.y] != NULL)
		{
			n.new[n.y] = (e->path_tex)[n.y];
			n.y++;
		}
		get_texture2(n, e);
	}
}

void	add_obj22_1(t_norme8 n, t_env *e, char *line, int *x)
{
	if (((n.tmp = get_number(line, x)) || 1) && n.tmp != 0)
		e->parse_obj->obj.radius = ft_clamp_min(
			ft_for_atof(line, n.y, *x), 0);
	else
		ft_error(N_NUM, "add_obj22");
}

void	add_obj22(char *line, int *x, t_env *e, char *rez)
{
	t_norme8	n;

	if (ft_strcmp(rez, "radius") == 0 && ((n.y = *x) || 1))
		add_obj22_1(n, e, line, x);
	else if (ft_strcmp(rez, "ind_refrac") == 0 && ((n.y = *x) || 1))
	{
		if ((n.tmp = get_number(line, x) || 1) && n.tmp != 0)
			e->parse_obj->obj.ind_refrac = ft_clamp(
				ft_for_atof(line, n.y, *x), 0, 3);
		else
			ft_error(N_NUM, "add_obj22");
	}
	else if (ft_strcmp(rez, "texture") == 0)
		get_texture(line, x, e);
	else if (ft_strcmp(rez, "negatif") == 0)
	{
		n.y = *x;
		if ((n.tmp = get_number(line, x)) && n.tmp == 1)
			e->parse_obj->obj.negatif = ft_clamp(ft_atoi(line + n.y), 0, 1);
	}
}
