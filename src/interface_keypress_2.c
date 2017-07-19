/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 16:18:11 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/13 17:51:16 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		clean_str(char **clean, int f)
{
	int		i;

	i = ft_strlen(*clean) - 1;
	if (f == 0)
	{
		while ((*clean)[i] == ' ' || (*clean)[i] == '\n' || (*clean)[i] == '\t')
			i--;
		(*clean)[i + 1] = '\0';
		return ;
	}
	else if (*clean && i >= 0)
	{
		while (i > 0)
			(*clean)[i--] = '\0';
		(*clean)[i] = '\0';
	}
}

void		free_env_parse(t_envg *e)
{
	free(e->e->cam);
	e->e->cam = NULL;
	while (e->e->parse_obj)
	{
		free(e->e->parse_obj);
		e->e->parse_obj = e->e->parse_obj->next;
	}
	while (e->e->parse_light)
	{
		free(e->e->parse_light);
		e->e->parse_light = e->e->parse_light->next;
	}
	e->e->parse_obj = NULL;
	e->e->parse_light = NULL;
	clean_str(&e->line[42], 0);
	ft_parse_j(e->line[42], e->e);
	init_id(e->e);
	clean_str(&e->line[42], 1);
	modif_default(e);
	home_tab(e);
}

int			failed_texture(t_envg *e, int i, int x)
{
	free(e->e->path_tex[x]);
	e->e->path_tex[x] = NULL;
	e->e->nb_tex--;
	e->error = i;
	home_tab(e);
	return (i);
}

int			add_texture(t_envg *e)
{
	int			x;
	char		*path;
	struct stat	test;

	x = 0;
	while (e->e->path_tex[x++])
		;
	e->e->nb_tex = x - 1;
	if (!(e->e->texture = (t_mlx *)malloc(sizeof(t_mlx) * x)))
		e->error = 6;
	x = -1;
	while (e->e->path_tex[++x])
	{
		path = ft_strjoin("./", e->e->path_tex[x]);
		// if (!ft_strcmp(path + (ft_strlen(path) - 4), ".png"))
		//     convert_file(&path);
		if (stat(path, &test) == -1)
			return (failed_texture(e, 7, x));
		if (!(e->e->texture[x].img = mlx_xpm_file_to_image(e->e->mlx->mlx,
				path, &e->e->texture[x].w, &e->e->texture[x].h)))
			return (failed_texture(e, 8, x));
		if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img,
				&e->e->texture[x].bpp,
				&e->e->texture[x].sizeline, &e->e->texture[x].endian)))
			return (failed_texture(e, 9, x));
	}
	return (-1);
}

void		add_new_texture(t_envg *e)
{
	char	**new;
	int		y;

	y = -1;
	clean_str(&e->line[41], 0);
	while ((e->e->path_tex)[++y] != NULL)
		if (ft_strcmp(e->line[41], (e->e->path_tex)[y]) == 0)
			break ;
	if ((e->e->path_tex)[y] == NULL)
	{
		if (!(new = (char **)malloc(sizeof(char *) * (y + 1))))
			ft_error(MALLOC, "add_new_texture => interface_keypress.c");
		y = -1;
		while ((e->e->path_tex)[++y] != NULL)
			new[y] = (e->e->path_tex)[y];
		new[y] = ft_strdup(e->line[41]);
		new[y + 1] = NULL;
		free(e->e->path_tex);
		e->e->path_tex = new;
		e->e->nb_tex++;
	}
	free(e->e->texture);
	e->error = add_texture(e);
	clean_str(&e->line[41], 1);
	home_tab(e);
}
