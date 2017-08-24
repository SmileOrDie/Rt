/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/02 13:24:29 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		put_img1(t_envg *e, int x, int y)
{
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, x, y);
}

static void		put_img2(t_envg *e, int i, int pos_x, int pos_y)
{
	if (i == 1)
		get_img(&e->mlx, &e->img, "./xpm_file/Check_V.xpm");
	else
	{
		get_img(&e->mlx, &e->img, "./xpm_file/Check_C.xpm");
		pos_y += 8;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, pos_x, pos_y);
}

static void		put_img3(t_envg *e)
{
	char		*str;
	int			img;
	t_parse_obj	*pos;

	img = e->i_lst + 15;
	while (e->i_lst < img && e->i_lst < e->nb_obj)
	{
		pos = srch_obj(e, srch_id(e, e->i_lst));
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, 40,
			200 + ((e->i_lst % 15) * 30));
		str = ft_strdup(pos->obj.name);
		string_put(e, (int[2]){70,
			200 + ((e->i_lst % 15) * 30)}, 0xFFFFFF, str);
		free(str);
		e->i_lst++;
	}
}

static void		put_img_2(t_envg *e)
{
	put_img2(e, ((e->filter.blue == 1) ? 1 : 0), 40, 522);
	put_img2(e, ((e->filter.green == 1) ? 1 : 0), 120, 522);
	put_img2(e, ((e->filter.red == 1) ? 1 : 0), 200, 522);
	put_img2(e, ((e->filter.sepia == 1) ? 1 : 0), 40, 547);
	put_img2(e, ((e->filter.old == 1) ? 1 : 0), 120, 547);
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
		put_img_2(e);
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
