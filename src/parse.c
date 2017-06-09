/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/18 15:36:43 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		add_lst_obj(t_env *e, t_obj obj)
{
	int i;
	t_parse_obj	*new;
	t_parse_obj	*b_obj;

	if (!(new  = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		ft_error(MALLOC, "creat_lst -> parce.c");
	obj.id = 0;
	new->obj = obj;
	new->next = NULL;
	if (!e->parse_obj)
		e->parse_obj = new;
	else
	{
		i = 0;
		b_obj = e->parse_obj;
		while (b_obj->next)
			b_obj = b_obj->next;
		new->obj.id = b_obj->obj.id + 1;
		b_obj->next = new;
	}
}

void		creat_lst(char **line, t_env *e, int count)
{
	int len;

	len = ft_tablen(&line, 0);
	if (len == 3 && ft_strcmp(line[0], "img_size") == 0 && e->flag == 0)
	{
		e->flag = 1;
		e->mlx->w = ft_atoi(line[1]);
		e->mlx->h = ft_atoi(line[2]);
	}
	else if (len > 7 && ft_strcmp(line[0], "light") != 0
		&& ft_strcmp(line[0], "cam") != 0)
	{
		add_lst_obj(e, add_obj(line, len, count));
		// printf("obj%s id%d\n", e->parse_obj->obj.name, e->parse_obj->obj.id);
	}
	else if ((len > 7 || len == 2) && (ft_strcmp(line[0], "light") == 0
		|| ft_strcmp(line[0], "cam") == 0 || !ft_strcmp(line[0], "ambient")))
		add_env(line, e);
	ft_tablen(&line, 1);
}

static void		ft_check_var(t_env *e)
{
	if (e->amb <= 0 || e->mlx->w <= 0 || e->mlx->h <= 0)
		ft_error("parse error :",
				" a variable ambient, width or height can't be <= 0");
	else if (e->cam == NULL)
		ft_error("camera error :", "no cam");
	else if (e->parse_obj == NULL)
		ft_error("object error : ", "no object");
}

void			ft_parse(char *name, t_env *e)
{
	int			fd;
	int			r;
	char		*line;
	int			c_line;

	e->flag = 0;
	c_line = 0;
	fd = open(name, O_RDONLY);
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		++c_line;
		if (*line && *line != '#')
			creat_lst(ft_strsplit(line, ' '), e, c_line);
		free(line);
		if (r == 0)
			break ;
	}
	close(fd);
	if (r == -1)
		ft_error(FILES_E, name);
	ft_check_var(e);
}
