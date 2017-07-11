/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/11 16:36:30 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

static void			put_img4(t_envg *e)
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

static void			put_img5_2(t_envg *e, unsigned char i)
{
	char					*str;

	if (e->line[30][0] == i + 1)
		get_img(e->mlx, &e->img, "./xpm_file/Select_On.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/Select_Off.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
		40, 600 + ((i % 3) * 30));
	str = ft_strdup(e->e->path_tex[i]);
	mlx_string_put(e->mlx->mlx, e->mlx->win,
		70, 600 + ((i % 3) * 30), 0xFFFFFF, str);
	free(str);
}

static void			put_img5(t_envg *e)
{
	unsigned char			i;
	t_parse_obj				*obj;

	i = e->page;
	printf("nb tex = %d i = %d\n", e->e->nb_tex, i);
	obj = srch_obj(e, e->obj);
	while (i < e->page + 3 && i < e->e->nb_tex)
	{
		put_img5_2(e, i);
		i++;
	}
	if (e->line[30][1] == 1)
		get_img(e->mlx, &e->img, "./xpm_file/Select_On.xpm");
	else
		get_img(e->mlx, &e->img, "./xpm_file/Select_Off.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, 160, 490);
	mlx_string_put(e->mlx->mlx, e->mlx->win, 185, 490, 0xFFFFFF, "Neg");
	if (e->page + 3 < e->e->nb_tex)
	{
		get_img(e->mlx, &e->img, "./xpm_file/next.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, 250, HE -
			250);
	}
	if (e->page >= 3)
	{
		get_img(e->mlx, &e->img, "./xpm_file/previous.xpm");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img, 50, HE -
			250);
	}
}

void				put_img_2(t_envg *e)
{
	put_img2(e, ((e->filter.blue == 1) ? 1 : 0), 40, 522);
	put_img2(e, ((e->filter.green == 1) ? 1 : 0), 120, 522);
	put_img2(e, ((e->filter.red == 1) ? 1 : 0), 200, 522);
	put_img2(e, ((e->filter.sepia == 1) ? 1 : 0), 40, 547);
	put_img2(e, ((e->filter.old == 1) ? 1 : 0), 120, 547);
}

void				put_img(t_envg *e, int img)
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
