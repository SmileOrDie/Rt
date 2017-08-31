/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/30 13:33:36 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void			get_img_2(t_env *e, unsigned char *img, t_n_g_img *n)
{
	n->i == 0 ? (n->tx = 0) : 0;
	n->color[0] = 0;
	n->color[1] = 0;
	n->color[2] = 0;
	n->tmpy = 0;
	while (n->tmpy < e->anti_a)
	{
		n->tmpx = 0;
		while (n->tmpx < e->anti_a)
		{
			n->opti[3] = n->tx * 4 + n->ty * e->win.w * 4 + n->tmpy * e->win.w
				* 4 + n->tmpx * 4;
			n->color[0] += img[n->opti[3] + 2];
			n->color[1] += img[n->opti[3] + 1];
			n->color[2] += img[n->opti[3] + 0];
			(n->tmpx)++;
		}
		(n->tmpy)++;
	}
	e->mlx.data[n->i * 4 + 0] = n->color[2] / n->opti[1];
	e->mlx.data[n->i * 4 + 1] = n->color[1] / n->opti[1];
	e->mlx.data[n->i * 4 + 2] = n->color[0] / n->opti[1];
	n->tx = (n->tx + e->anti_a) % e->win.w;
	n->tx == 0 ? n->ty += e->anti_a : 0;
	(n->i)++;
}

void				get_image(t_env *e)
{
	t_n_g_img		n;
	t_color2		pixel;
	char			flag;
	unsigned char	*img;

	flag = 1;
	n.i = -1;
	n.opti[0] = e->win.h * e->win.w;
	n.opti[1] = e->anti_a * e->anti_a;
	n.opti[2] = n.opti[0] / n.opti[1];
	if (!(img = malloc(n.opti[0] * 4)))
		ft_error(MALLOC, "get_image");
	while (++(n.i) < n.opti[0])
	{
		pixel = get_pixel(e->tab_three[n.i], (t_color2){0, 0, 0, 0}, e->cl_e,
		(t_g_pix){flag, e->coef_t[n.i], 0});
		img[n.i * 4 + 2] = pixel.r;
		img[n.i * 4 + 1] = pixel.g;
		img[n.i * 4 + 0] = pixel.b;
		flag = 0;
	}
	n.i = 0;
	while (((n.i == 0 && (n.ty = 0)) || 1) && n.i < n.opti[2])
		get_img_2(e, img, &n);
	free(img);
}

void				parse_file(char *name, t_envg *e)
{
	int		len_name;

	len_name = ft_strlen(name);
	if (!ft_strcmp(name + (len_name - 5), ".json"))
		ft_parse_j(name, e);
	init_id(e);
}

int					main(int ac, char **av)
{
	t_envg		e;
	t_env		env;

	e.anti_a = 1;
	e.path_tex = NULL;
	e.e = &env;
	e.nb_tex = 0;
	e.parse_light = NULL;
	e.parse_obj = NULL;
	if (!(e.cl_e = (t_env_cl *)malloc(sizeof(t_env_cl))))
		ft_error(MALLOC, "opencl.c => void ft_init_opencl(...)");
	if (!(e.cl_e->cl = (t_opencl *)malloc(sizeof(t_opencl))))
		ft_error(MALLOC, "opencl.c => void ft_init_opencl(...)");
	if (ac == 2)
		parse_file(av[1], &e);
	ft_init_opencl(&e, e.cl_e->cl);
	graphic_interface(&e);
	return (1);
}
