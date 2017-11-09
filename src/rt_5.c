/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:55:29 by phmoulin          #+#    #+#             */
/*   Updated: 2017/11/09 13:31:26 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void			create_sdl_texture(t_envg *e, char *path, int x)
{
	SDL_Surface		*surface;

	if ((surface = IMG_Load(path)))
	{
		e->e->texture[x].data = (char *)ft_strsub2(surface->pixels,
			(size_t)surface->h * (size_t)surface->w * 4, surface);
		e->e->texture[x].h = surface->h;
		e->e->texture[x].w = surface->w;
		e->e->texture[x].crenelage = 2;
		SDL_FreeSurface(surface);
	}
	else
		ft_error("SDL2 : ", (char *)SDL_GetError());
}

void				all_texture(t_envg *e, char *path, int x)
{
	int				l;

	l = (ft_strlen(path) - 4);
	if (ft_strcmp(path + l, ".xpm") == 0 || ft_strcmp(path + l, ".XPM") == 0)
	{
		(!(e->e->texture[x].img = mlx_xpm_file_to_image(e->mlx.mlx, path, &e->e
->texture[x].w, &e->e->texture[x].h))) ? ft_error(MLX, "IMG") : 0;
		if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img,
&e->e->texture[x].bpp, &e->e->texture[x].sizeline, &e->e->texture[x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
		e->e->texture[x].crenelage = 1;
	}
	else
		create_sdl_texture(e, path, x);
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
	if (!(e->e->texture = (t_mlx *)malloc(sizeof(t_mlx) * x)))
		ft_error(MALLOC, "ft_get_image_texture");
	x = 0;
	while (e->path_tex && e->path_tex[x])
	{
		path = ft_strjoin("./", e->path_tex[x]);
		if (stat(path, &test) == -1)
			ft_error("File texture doesn't exist : ", path);
		all_texture(e, e->path_tex[x], x);
		free(path);
		x++;
	}
}
