/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:55:29 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/28 18:56:07 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void				all_texture(t_envg *e, char *path, int x)
{
	SDL_Surface		*surface;
	int				l;

	l = (ft_strlen(path) - 4);
	if (ft_strcmp(path + l, ".xpm") == 0 || ft_strcmp(path + l, ".XPM") == 0)
	{
		if (!(e->e->texture[x].img = mlx_xpm_file_to_image(e->mlx.mlx, path,
			&e->e->texture[x].w, &e->e->texture[x].h)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
		if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img,
&e->e->texture[x].bpp, &e->e->texture[x].sizeline, &e->e->texture[x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
	}
	else
	{
		if ((surface = IMG_Load(path)))
		{
			e->e->texture[x].data = (char *)(surface->pixels);
			e->e->texture[x].h = surface->h;
			e->e->texture[x].w = surface->w;
		}
		else
			ft_error("SDL2 : ", ft_strjoin("IMG_Load(...) -> failed : ",
				SDL_GetError()));
	}
}

void				ft_get_image_texture(t_envg *e)
{
	int			x;
	char		*path;
	struct stat	test;

	x = 0;
	while (e->path_tex && e->path_tex[x])
		x++;
	e->nb_tex = x;
	e->e->texture = malloc(sizeof(t_mlx) * x);
	x = 0;
	while (e->path_tex && e->path_tex[x])
	{
		path = ft_strjoin("./", e->path_tex[x]);
		if (stat(path, &test) == -1)
			ft_error("File texture doesn't exist : ", path);
		all_texture(e, e->path_tex[x], x);
		x++;
	}
}
