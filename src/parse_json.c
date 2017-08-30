/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/03 18:44:06 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			get_image_size(char *line, int *x, t_envg *e)
{
	int	y;
	int	tmp;

	line[*x] != '[' ?
		ft_error(J_SON, "get_image_size") : (*x)++;
	free_space(line, x);
	y = *x;
	tmp = get_number(line, x);
	if (tmp == 1)
		e->win.w = ft_atoi(line + y);
	else
		ft_error(N_NUM, "get_image_size");
	free_space(line, x);
	line[*x] != ',' ?
		ft_error(J_SON, "get_image_size") : (*x)++;
	free_space(line, x);
	y = *x;
	tmp = get_number(line, x);
	if (tmp == 1)
		e->win.h = ft_atoi(line + y);
	else
		ft_error(N_NUM, "get_image_size");
	free_space(line, x);
	line[*x] != ']' ?
	ft_error(J_SON, "get_image_size") : (*x)++;
}

void			ft_check_obj_neg(t_envg *e)
{
	t_parse_obj	*tmp;

	tmp = e->parse_obj;
	while (tmp)
	{
		if (tmp->obj.negatif > 0)
		{
			tmp->obj.color = (t_color2){255, 255, 255, 0};
			tmp->obj.ind_transp = 1;
			tmp->obj.ind_reflec = 0;
			tmp->obj.ind_refrac = 1;
			tmp->obj.id_texture = 0;
		}
		tmp = tmp->next;
	}
	tmp = e->parse_obj;
}

void			ft_parse_j(char *name, t_envg *e)
{
	int			fd;
	int			i;
	struct stat	st;
	char		*line;

	i = 0;
	e->parse_light = NULL;
	e->parse_obj = NULL;
	stat(name, &st) != 0 ? ft_error("File doesn't exist : ", name) : 0;
	(fd = open(name, O_RDONLY)) < 0 ? ft_error("Can't open file : ", name) : 0;
	(line = (char*)malloc(sizeof(char) * (st.st_size + 1))) ? 0 :
	ft_error(MALLOC, name);
	line[st.st_size] = '\0';
	read(fd, line, st.st_size);
	close(fd);
	ft_parse_json(line, e);
	e->win.h *= e->anti_a;
	e->win.w *= e->anti_a;
	get_camera3(e);
	free(line);
	ft_check_obj_neg(e);
	while (e->path_tex && e->path_tex[i])
		i++;
	e->e->nb_tex = i;
	e->nb_tex = i;
}
