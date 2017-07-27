/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/27 13:53:02 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"


///////////////////////sa sert a quoi ???????????????????
// void		put_img5(t_envg *e)
// {
// 	int				img;
// 	char			*str;
// 	t_parse_light	*b;
//
// 	img = e->page + 3;
// 	e->i_lst = e->page;
// 	b = srch_light(e, e->i_lst);
// 	while (e->i_lst < img && b)
// 	{
// 		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
// 			40, 400 + ((e->i_lst % 3) * 30));
// 		get_img(e->mlx, &e->img, "./xpm_file/deleted.xpm");
// 		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
// 			60, 400 + ((e->i_lst % 3) * 30));
// 		get_img(e->mlx, &e->img, "./xpm_file/Modify.xpm");
// 		str = ft_strdup(b->light.name);
// 		mlx_string_put(e->mlx->mlx, e->mlx->win,
// 			90, 400 + ((e->i_lst % 3) * 30), 0xFFFFFF, str);
// 		free(str);
// 		e->i_lst++;
// 		b = b->next;
// 	}
// }

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

	anti_a = ft_itoa(e->anti_a);
	get_img(e->mlx, &e->img, "xpm_file/Anti_a.xpm");
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->img.img,
			45, 600);
	mlx_string_put(e->mlx->mlx, e->mlx->win,
			75, 622, 0x000000, anti_a);
	free(anti_a);
}
