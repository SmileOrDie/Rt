/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/29 12:01:30 by pde-maul         ###   ########.fr       */
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

void			ft_creat_lst_obj(t_env *e)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;
	int					i;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7)
			i += 2;
		else if (parse_obj_b->obj.type == 8)
			i++;
		else if (parse_obj_b->obj.type == 9)
			i += 2;
		parse_obj_b = parse_obj_b->next;
		i++;
	}
	e->nb_obj = i;
	i = 0;
	while (parse_light_b)
	{
		parse_light_b = parse_light_b->next;
		i++;
	}
	e->nb_light = i;
	if (!(e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->nb_obj)))
		ft_error(MALLOC, "e->l_obj -> rt.h");
	if (!(e->light = (t_light *)malloc(sizeof(t_light) * e->nb_light)))
		ft_error(MALLOC, "e->light -> rt.h");
	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		if (parse_obj_b->obj.type == 7 || parse_obj_b->obj.type == 8 ||
			parse_obj_b->obj.type == 9)
			get_obj_lst(e, parse_obj_b->obj, &i);
		else
		{
			e->l_obj[i] = parse_obj_b->obj;
			e->l_obj[i].id = i;
		}
		i++;
		parse_obj_b = parse_obj_b->next;
	}
	i = 0;
	while (parse_light_b)
	{
		e->light[i] = parse_light_b->light;
		parse_light_b = parse_light_b->next;
		i++;
	}
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
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
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
