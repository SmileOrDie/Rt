/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_put_img_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 12:03:34 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/22 18:50:39 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		put_img6(t_envg *e)
{
	if (!e->line[41][0])
		get_img(&e->mlx, &e->img, "./xpm_file/Send.xpm");
	else
		get_img(&e->mlx, &e->img, "./xpm_file/send_v.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
		290, 240);
	if (!e->line[42][0])
		get_img(&e->mlx, &e->img, "./xpm_file/Send.xpm");
	else
		get_img(&e->mlx, &e->img, "./xpm_file/send_v.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
		290, 295);
	if (e->nb_obj > 0 && e->cam.set)
		get_img(&e->mlx, &e->img, "./xpm_file/Save_scene_v.xpm");
	else
		get_img(&e->mlx, &e->img, "./xpm_file/Save_scene_f.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
		40, 330);
	if (e->e && e->e->mlx.img != NULL)
		get_img(&e->mlx, &e->img, "./xpm_file/Save_img_v.xpm");
	else
		get_img(&e->mlx, &e->img, "./xpm_file/Save_img_f.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
		145, 330);
}

void		put_img7(t_envg *e)
{
	char *anti_a;

	anti_a = ft_itoa(e->anti_a);
	get_img(&e->mlx, &e->img, "xpm_file/Anti_a.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			45, 600);
	string_put(e,
			(int[2]){75, 622}, 0x000000, anti_a);
	free(anti_a);
}

void		put_img8(t_envg *e)
{
	char *amb;

	amb = ft_dtoa(e->amb);
	amb[4] = '\0';
	get_img(&e->mlx, &e->img, "xpm_file/Ambient.xpm");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img,
			160, 600);
	string_put(e,
			(int[2]){190, 622}, 0x000000, amb);
	free(amb);
}
