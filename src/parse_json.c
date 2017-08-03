/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/02 19:37:40 by shamdani         ###   ########.fr       */
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
			tmp->obj.ind_refrac = e->e->default_indice;
			printf("--\n");
		}
		tmp = tmp->next;
	}
	tmp = e->parse_obj;
	while (tmp)
	{
		printf("id = %d, name = %s, negatif = %d, tmp->obj.color = %d %d %d, tmp->obj.ind_transp = %f, tmp->obj.ind_reflec = %f, tmp->obj.ind_refrac = %f\n", tmp->obj.id, tmp->obj.name, tmp->obj.negatif, tmp->obj.color.r, tmp->obj.color.g, tmp->obj.color.b, tmp->obj.ind_transp, tmp->obj.ind_reflec, tmp->obj.ind_refrac);
		tmp = tmp->next;
	}
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
	if (stat(name, &st) != 0)
		ft_error("File doesn't exist : ", name);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open file : ", name);
	line = malloc(st.st_size + 1);
	line[st.st_size] = '\0';
	read(fd, line, st.st_size);
	close(fd);
	ft_parse_json(line, e);
	e->win.h *= e->anti_a;
	e->win.w *= e->anti_a;
	get_camera3(e);
	free(line);
	ft_check_obj_neg(e);
 	while(e->path_tex && e->path_tex[i])
	 	i++;
	e->e->nb_tex = i;
	e->nb_tex = i;
	// printf("e->parse_obj.id = %d et e->parse_obj.ind_transp = %f, e->parse_obj.name = %s\n", e->parse_obj->obj.id, e->parse_obj->obj.ind_transp, e->parse_obj->obj.name);
}
