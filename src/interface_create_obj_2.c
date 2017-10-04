/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:24:19 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/24 19:05:40 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_parse_obj		*srch_obj(t_envg *e, int id)
{
	t_parse_obj *obj_lst;

	obj_lst = e->parse_obj;
	while (obj_lst)
	{
		if (obj_lst->obj.id == id)
			return (obj_lst);
		obj_lst = obj_lst->next;
	}
	return (NULL);
}

t_parse_light	*srch_light(t_envg *e, int id)
{
	t_parse_light	*light_lst;
	int				index;

	index = 0;
	light_lst = e->parse_light;
	while (light_lst)
	{
		if (index == id)
			return (light_lst);
		light_lst = light_lst->next;
		index++;
	}
	return (NULL);
}

void			reset_line(char **line)
{
	int				i;
	int				len;

	i = 0;
	while (++i <= 15)
	{
		len = ft_strlen(line[i]);
		while (len >= 0)
			line[i][len--] = '\0';
	}
	len = ft_strlen(line[31]);
	while (len >= 0)
		line[31][len--] = '\0';
}

t_light			new_light(t_envg *e)
{
	t_light			l;

	l.pos = new_v(ft_atod(e->line[3]), ft_atod(e->line[4]),
		ft_atod(e->line[5]));
	l.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]),
		ft_atoi(e->line[11]), 0};
	l.name = ft_strdup(e->line[2]);
	return (l);
}
