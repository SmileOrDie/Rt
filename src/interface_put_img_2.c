/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 17:04:57 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/04 13:17:19 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		put_img4(t_envg *e)
{
	int				img;
	char			*str;
	t_parse_light	*b;

	img = e->page + 3;
	e->i_lst = e->page;
	b = srch_light(e, e->i_lst);
	while (e->i_lst < img && b)
	{
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			40, 400 + ((e->i_lst % 3) * 30));
		get_img(&e->mlx, &e->img, "./xpm_file/deleted.xpm");
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			60, 400 + ((e->i_lst % 3) * 30));
		get_img(&e->mlx, &e->img, "./xpm_file/Modify.xpm");
		str = ft_strdup(b->light.name);
		string_put(e,
			(int[2]){90, 400 + ((e->i_lst % 3) * 30)}, 0xFFFFFF, str);
		free(str);
		e->i_lst++;
		b = b->next;
	}
}

void		put_img5_2(t_envg *e)
{
	if (e->line[30][1] == 1)
		get_img(&e->mlx, &e->img, "./xpm_file/Select_On.xpm");
	else
		get_img(&e->mlx, &e->img, "./xpm_file/Select_Off.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			160, 490);
	string_put(e,
			(int[2]){185, 490}, 0xFFFFFF, "Neg");
	if (e->nb_tex > 0 && e->page + 3 < e->nb_tex)
	{
		get_img(&e->mlx, &e->img, "./xpm_file/next.xpm");
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			250, HE - 250);
	}
	if (e->nb_tex > 0 && e->page >= 3)
	{
		get_img(&e->mlx, &e->img, "./xpm_file/previous.xpm");
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			50, HE - 250);
	}
}

void		put_img5(t_envg *e)
{
	unsigned char	i;

	i = e->page;
	while (i < e->page + 3 && i < e->nb_tex)
	{
		if (e->line[30][0] == i + 1)
			get_img(&e->mlx, &e->img, "./xpm_file/Select_On.xpm");
		else
			get_img(&e->mlx, &e->img, "./xpm_file/Select_Off.xpm");
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			40, 600 + ((i % 3) * 30));
		string_put(e,
			(int[2]){70, 600 + ((i % 3) * 30)}, 0xFFFFFF, e->path_tex[i]);
		i++;
	}
	put_img5_2(e);
}
