/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 19:14:12 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			put_img3(t_envg *e)
{
	char		*str;
	int			img;
	int			nb_obj;
	t_parse_obj	*pos;

	img = e->i_lst + 15;
	nb_obj = 0;
	pos = e->e->parse_obj;
	while (pos)
	{
		nb_obj++;
		pos = pos->next;
	}
	while (e->i_lst < img && e->i_lst < nb_obj)
	{
		pos = srch_obj(e, e->i_lst);
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, 40,
			200 + ((e->i_lst % 15) * 30));
		str = ft_strdup(pos->obj.name);
		mlx_string_put(e->mlx->mlx, e->mlx->win, 70,
			200 + ((e->i_lst % 15) * 30), 0xFFFFFF, str);
		free(str);
		e->i_lst++;
	}
}

void			put_img1(t_envg *e, int x, int y)
{
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, x, y);
}

void			put_img2(t_envg *e, int i, int pos_x, int pos_y)
{
	if (i == 1)
		get_img(e->mlx, &e->img, "./xpm_file/Check_V.xpm");
	else
	{
		get_img(e->mlx, &e->img, "./xpm_file/Check_C.xpm");
		pos_y += 8;
	}
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, pos_x, pos_y);
}

void			put_img5(t_envg *e)
{
	int				img;
	char			*str;
	t_parse_light	*b;

	img = e->page + 3;
	e->i_lst = e->page;
	b = srch_light(e, e->i_lst);
	while (e->i_lst < img && b)
	{
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			40, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/deleted.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			60, 400 + ((e->i_lst % 3) * 30));
		get_img(e->mlx, &e->img, "./xpm_file/Modify.xpm");
		str = ft_strdup(b->light.name);
		mlx_string_put(e->mlx->mlx, e->mlx->win,
			90, 400 + ((e->i_lst % 3) * 30), 0xFFFFFF, str);
		free(str);
		e->i_lst++;
		b = b->next;
	}
}

void		put_img6(t_envg *e)
{
	if (!e->line[41][0])
		get_img(e->mlx, &e->img, "./xpm_file/Send.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/send_v.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
		290, 240);
	if (!e->line[42][0])
		get_img(e->mlx, &e->img, "./xpm_file/Send.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/send_v.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
		290, 295);
	if (e->e->nb_obj > 0 && e->e->cam != NULL)
		get_img(e->mlx, &e->img, "./xpm_file/Save_scene_v.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/Save_scene_f.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
		40, 330);
	if (e->e && e->e->mlx->img != NULL)
		get_img(e->mlx, &e->img, "./xpm_file/Save_img_v.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/Save_img_f.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
		145, 330);
}

void		put_img7(t_envg *e)
{
	char *anti_a;

	anti_a = ft_itoa(e->e->anti_a);
	get_img(e->mlx, &e->img, "xpm_file/Anti_a.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			45, 600);
	mlx_string_put(e->mlx->mlx, e->mlx->win,
			75, 622, 0x000000, anti_a);
	free(anti_a);
}
