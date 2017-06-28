/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:47:47 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 15:16:36 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			clean_str(char **clean, int f)
{
	int		i;

	i = ft_strlen(*clean) - 1;
	if (f == 0)
	{
		while ((*clean)[i] == ' ' || (*clean)[i] == '\n' || (*clean)[i] == '\t')
			i--;
		(*clean)[i + 1] = '\0';
	}
	else
	{
		while (i)
			(*clean)[i--] = '\0';
		(*clean)[i] = '\0';
	}
}

int				failed_texture(t_envg *e, int i, int x)
{
	free(e->e->path_tex[x]);
	e->e->path_tex[x] = NULL;
	e->e->nb_tex--;
	e->error = i;
	home_tab(e);
	return (i);
}

int				add_texture2(t_envg *e, int x)
{
	struct stat		test;
	char			*path;

	path = ft_strjoin("./", e->e->path_tex[x]);
	if (stat(path, &test) == -1)
		return (failed_texture(e, 7, x));
	if (!(e->e->texture[x].img = mlx_xpm_file_to_image(e->e->mlx->mlx, \
		path, &e->e->texture[x].w, &e->e->texture[x].h)))
		return (failed_texture(e, 8, x));
	if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img, \
		&e->e->texture[x].bpp, &e->e->texture[x].sizeline, \
		&e->e->texture[x].endian)))
		return (failed_texture(e, 9, x));
	return (0);
}

int				add_texture(t_envg *e)
{
	int				x;

	x = 0;
	while (e->e->path_tex[x])
		x++;
	e->e->nb_tex = x;
	if (!(e->e->texture = (t_mlx *)malloc(sizeof(t_mlx) * x)))
		e->error = 6;
	x = 0;
	while (e->e->path_tex[x])
	{
		add_texture2(e, x);
		x++;
	}
	clean_str(&e->line[e->pos], 1);
	home_tab(e);
	return (-1);
}
