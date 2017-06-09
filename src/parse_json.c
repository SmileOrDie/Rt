/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/07 12:27:36 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			get_image_size(char *line, int *x, t_env *e)
{
	int	y;
	int	tmp;

	line[*x] != '[' ?
		ft_error(J_SON, "get_image_size") : (*x)++;
	free_space(line, x);
	y = *x;
	tmp = get_number(line, x);
	if (tmp == 1)
		e->mlx->w = ft_atoi(line + y);
	else
		ft_error(N_NUM, "get_image_size");
	free_space(line, x);
	line[*x] != ',' ?
		ft_error(J_SON, "get_image_size") : (*x)++;
	free_space(line, x);
	y = *x;
	tmp = get_number(line, x);
	if (tmp == 1)
		e->mlx->h = ft_atoi(line + y);
	else
		ft_error(N_NUM, "get_image_size");
	free_space(line, x);
	line[*x] != ']' ?
	ft_error(J_SON, "get_image_size") : (*x)++;
}

void			ft_parse_j(char *name, t_env *e)
{
	int			fd;
	struct stat	st;
	char		*line;

	e->flag = 0;
	e->parse_light = NULL;
	e->parse_obj = NULL;
	if (stat(name, &st) != 0)
		ft_error("File doesn't exist", "ft_parse");
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open file", "ft_parse");
	line = malloc(st.st_size + 1);
	line[st.st_size] = '\0';
	read(fd, line, st.st_size);
	close(fd);
	ft_parse_json(line, e);
	free(line);
}
