/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/08 11:22:56 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

static void		init(t_env *e)
{
	if (!(e->cl_e = (t_env_cl *)malloc(sizeof(t_env_cl))))
		ft_error(MALLOC, "rtv1.c => int main(...)");
	if (!(e->cl_e->cl = (t_opencl *)malloc(sizeof(t_opencl))))
		ft_error(MALLOC, "rtv1.c => int main(...)");
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error(MALLOC, "int	ft_parse(char *name, t_env *e)(e->mlx)");
	e->light = NULL;
	e->l_obj = NULL;
	e->cam = NULL;
	e->mlx->w = W;
	e->mlx->h = H;
	e->amb = 0.1;
	e->b_screen = 1;
	e->nb_obj = 0;
	e->nb_light = 0;
	e->default_indice = 1;
}

void			ft_get_image_texture(t_env *e)
{
	int			x;
	char		*path;
	struct stat	test;

	x = 0;
	while (e->path_tex[x])
		x++;
	e->nb_tex = x;
	e->texture = malloc(sizeof(t_mlx) * x);
	x = 0;
	while (e->path_tex[x])
	{
		path = ft_strjoin("./", e->path_tex[x]);
		if (stat(path, &test) == -1)
			ft_error("File texture doesn't exist : ", path);
		if (!(e->texture[x].img = mlx_xpm_file_to_image(e->mlx->mlx, path, \
			&e->texture[x].w, &e->texture[x].h)))
		{
			printf("2str= %s\n", path);
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
		}
		if (!(e->texture[x].data = mlx_get_data_addr(e->texture[x].img,
			&e->texture[x].bpp, &e->texture[x].sizeline, \
			&e->texture[x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
		x++;
	}
}

void			parse_file(char *name, t_env *e)
{
	int		len_name;

	len_name = ft_strlen(name);
	e->parse_light = NULL;
	e->parse_obj = NULL;
	if (!ft_strcmp(name + (len_name - 5), ".json"))
		ft_parse_j(name, e);
	init_id(e);
}

int				main(int ac, char **av)
{
	t_env		e;

	init(&e);
	e.anti_a = 1;
	e.path_tex = malloc(sizeof(char *));
	e.path_tex[0] = NULL;
	if (ac == 2)
		parse_file(av[1], &e);
	ft_init_opencl(&e, e.cl_e->cl);
	graphic_interface(&e);
	return (1);
}
