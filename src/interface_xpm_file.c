/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_xpm_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:14:40 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/02 20:07:02 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void				get_img(t_mlx *mlx, t_mlx *img, char *str)
{
	if (img->img)
		mlx_destroy_image(mlx->mlx, img->img);
	if (!(img->img = mlx_xpm_file_to_image(mlx->mlx, str, &img->w, &img->h)))
		ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
}

static void			load_img1(t_envg *e, char *img_path[31], int img)
{
	img_path[22] = "./xpm_file/Previous_light.xpm";
	img_path[23] = "./xpm_file/Next_light.xpm";
	img_path[24] = "./xpm_file/Check_C.xpm";
	img_path[25] = "./xpm_file/Check_V.xpm";
	img_path[26] = "./xpm_file/Error.xpm";
	img_path[27] = "./xpm_file/Play.xpm";
	img_path[28] = "./xpm_file/Stop.xpm";
	img_path[29] = "./xpm_file/Select_Off.xpm";
	img_path[30] = "./xpm_file/Select_On.xpm";
	get_img(&e->mlx, &e->img, img_path[img]);
	put_img(e, (img == 20) ? 17 : img);
}

void				load_img(t_envg *e, int img)
{
	char	*img_path[31];

	img_path[0] = "./xpm_file/Font_RT.xpm";
	img_path[1] = "./xpm_file/Volet_Home2.xpm";
	img_path[2] = "./xpm_file/Volet_Add2.xpm";
	img_path[3] = "./xpm_file/Volet_Config2.xpm";
	img_path[4] = "./xpm_file/Volet_Delete2.xpm";
	img_path[5] = "./xpm_file/Volet_About2.xpm";
	img_path[6] = "./xpm_file/Standard_Bar.xpm";
	img_path[7] = "./xpm_file/Standard_Bar_Select.xpm";
	img_path[8] = "./xpm_file/Number_Bar.xpm";
	img_path[9] = "./xpm_file/Number_Bar_Select.xpm";
	img_path[10] = "./xpm_file/Vector_Bar.xpm";
	img_path[11] = "./xpm_file/Vector_Bar_Select.xpm";
	img_path[12] = "./xpm_file/New_Title.xpm";
	img_path[13] = "./xpm_file/Add_Button.xpm";
	img_path[14] = "./xpm_file/Object_Type.xpm";
	img_path[15] = "./xpm_file/Modify.xpm";
	img_path[16] = "./xpm_file/previous.xpm";
	img_path[17] = "./xpm_file/next.xpm";
	img_path[18] = "./xpm_file/Conf_Title.xpm";
	img_path[19] = "./xpm_file/deleted.xpm";
	img_path[20] = "./xpm_file/mod_button.xpm";
	img_path[21] = "./xpm_file/Modify.xpm";
	load_img1(e, img_path, img);
}
