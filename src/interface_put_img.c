/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/21 16:49:29 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		put_img1(t_envg *e, int x, int y)
{
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, x , y);
}

static void		put_img2(t_envg *e, int i, int pos_x, int pos_y)
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

static void		put_img3(t_envg *e)
{
	char *str;
	int img;
	int nb_obj;
	t_parse_obj *pos;

	img = e->i_lst + 15;
	nb_obj = 0 ;
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

static void		put_img4(t_envg *e)
{
	int img;
	char *str;
	t_parse_light *b;


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
			90, 400 + ((e->i_lst % 3)* 30), 0xFFFFFF, str);
		free(str);
		e->i_lst++;
		b = b->next;
	}
}

// int check_textur(t_envg *e)
// {
	// if (!)
// }

static void		put_img5(t_envg *e)
{
	char					*str;
	unsigned char			i;
	t_parse_obj				*obj;

	i = e->page;
	obj = srch_obj(e, e->obj + e->page);
	while (obj && i < e->page + 3 && i < e->e->nb_tex)
	{
		if (obj && obj->obj.id_texture == i + 1)
			get_img(e->mlx, &e->img, "./xpm_file/Select_On.xpm");
		else
			get_img(e->mlx, &e->img, "./xpm_file/Select_Off.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			40, 600 + ((i % 3) * 30));
		str = ft_strdup(e->e->path_tex[i]);
		mlx_string_put(e->mlx->mlx, e->mlx->win,
			70, 600 + ((i % 3) * 30), 0xFFFFFF, str);
		free(str);
		i++;
	}
	if (e->page + 3 < e->e->nb_tex)
	{
		get_img(e->mlx, &e->img, "./xpm_file/next.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			250, HE - 250);
	}
	if (e->page >= 3)
	{
		get_img(e->mlx, &e->img, "./xpm_file/previous.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			50, HE - 250);
	}
}

void			put_img(t_envg *e, int img)
{
	if (img > 0 && img < 6)
		put_img1(e, 0, HE - e->img.h);
	else if (img > 5 && img < 15)
		put_img1(e, e->line_pos[e->pos].w, e->line_pos[e->pos].h);
	else if (img == 15 || img == 19)
		put_img3(e);
	else if (img == 24)
	{
		put_img2(e, ((e->filter.blue == 1) ? 1 : 0), 40, 522);
		put_img2(e, ((e->filter.green == 1) ? 1 : 0), 120, 522);
		put_img2(e, ((e->filter.red == 1) ? 1 : 0), 200, 522);
		put_img2(e, ((e->filter.sepia == 1) ? 1 : 0), 40, 547);
		put_img2(e, ((e->filter.old == 1) ? 1 : 0), 120, 547);
		put_img2(e, ((e->filter.cartoon == 1) ? 1 : 0), 200, 547);
	}
	else if (img == 21)
		put_img4(e);
	else if (img >= 16 && img <= 18)
		put_img1(e, e->line_pos[img].w, e->line_pos[img].h);
	else if (img == 22 || img == 23)
		put_img1(e, (img == 23) ? WI - 100 : WI - 130, 490);
	else if (img >= 26 && img <= 28)
		put_img1(e, e->line_pos[img + 1].w, e->line_pos[img + 1].h);
	else if (img == 29)
		put_img5(e);
	else
		put_img1(e, 0, 0);
}
