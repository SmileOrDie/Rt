/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 17:07:15 by pde-maul         ###   ########.fr       */
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
	t_norme14	n;

	n.x = 0;
	while (e->path_tex[n.x])
		n.x++;
	e->nb_tex = n.x;
	e->texture = malloc(sizeof(t_mlx) * n.x);
	n.x = 0;
	while (e->path_tex[n.x])
	{
		n.path = ft_strjoin("./", e->path_tex[n.x]);
		if (stat(n.path, &n.test) == -1)
			ft_error("File texture doesn't exist : ", n.path);
		if (!(e->texture[n.x].img = mlx_xpm_file_to_image(e->mlx->mlx, n.path,\
			&e->texture[n.x].w, &e->texture[n.x].h)))
		{
			printf("2str= %s\n", n.path);
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
		}
		if (!(e->texture[n.x].data = mlx_get_data_addr(e->texture[n.x].img,
			&e->texture[n.x].bpp, &e->texture[n.x].sizeline, \
			&e->texture[n.x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
		n.x++;
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
