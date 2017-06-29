/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:53:01 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 11:56:16 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

t_color2		get_pixel(t_three *branch, t_color2 pixel, t_env_cl *e, char flag, double coef_t)
{
	t_color2			color_ray;
	static int			i = 0;

	flag ? (i = 0) : 0;
	if (!branch)
		return ((t_color2){0, 0, 0, 0});
	if (branch->r_reflec)
	{
		color_ray = get_pixel(branch->r_reflec, pixel, e, 0, coef_t);
		color_ray = mult_color(color_ray, branch->p_hit.coef * \
			e->l_obj[branch->id].ind_reflec);
		pixel = add_color(pixel, color_ray);
	}
	if (branch->r_refrac)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		color_ray.r = color_ray.r * (branch->c_origin.r / 255.0);
		color_ray.g = color_ray.g * (branch->c_origin.g / 255.0);
		color_ray.b = color_ray.b * (branch->c_origin.b / 255.0);
		color_ray = mult_color(color_ray, branch->p_hit.coef * \
			e->l_obj[branch->id].ind_transp * \
			(1 - e->l_obj[branch->id].ind_reflec));
		pixel = add_color(pixel, color_ray);
	}
	if (branch->p_hit.coef * (1 - e->l_obj[branch->id].ind_transp) * \
	(1 - e->l_obj[branch->id].ind_reflec) > 0.04)
	{
		color_ray = mult_color((t_color2){(unsigned char)e->color_lst[i].r, \
			(unsigned char)e->color_lst[i].g, \
			(unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef * \
			(1 - e->l_obj[branch->id].ind_transp) * \
			(1 - e->l_obj[branch->id].ind_reflec) / coef_t);
		pixel = add_color(pixel, color_ray);
		i++;
	}
	return (pixel);
}

void			get_image(t_env *e)
{
	int				i;
	int				tx;
	int				ty;
	int				tmpx;
	int				tmpy;
	t_color2		pixel;
	char			flag;
	unsigned char	*img;
	int				color[3];

	flag = 1;
	i = 0;
	img = malloc(e->mlx->h * e->mlx->w * 4);
	while (i < e->mlx->h * e->mlx->w)
	{
		pixel = get_pixel(e->tab_three[i], (t_color2){0, 0, 0, 0}, e->cl_e, \
		flag, e->coef_t[i]);
		img[i * 4 + 2] = pixel.r;
		img[i * 4 + 1] = pixel.g;
		img[i * 4 + 0] = pixel.b;
		i++;
		flag = 0;
	}
	i = 0;
	tx = 0;
	ty = 0;
	while (i < e->mlx->h * e->mlx->w / e->anti_a / e->anti_a)
	{
		tmpy = 0;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		while (tmpy < e->anti_a)
		{
			tmpx = 0;
			while (tmpx < e->anti_a)
			{
				color[0] += img[tx * 4 + ty * e->mlx->w * 4 + 2 + tmpy * \
				e->mlx->w * 4 + tmpx * 4];
				color[1] += img[tx * 4 + ty * e->mlx->w * 4 + 1 + tmpy * \
				e->mlx->w * 4 + tmpx * 4];
				color[2] += img[tx * 4 + ty * e->mlx->w * 4 + 0 + tmpy * \
				e->mlx->w * 4 + tmpx * 4];
				tmpx++;
			}
			tmpy++;
		}
		e->mlx->data[i * 4 + 0] = color[2] / e->anti_a / e->anti_a;
		e->mlx->data[i * 4 + 1] = color[1] / e->anti_a / e->anti_a;
		e->mlx->data[i * 4 + 2] = color[0] / e->anti_a / e->anti_a;
		i++;
		tx = (tx + e->anti_a) % e->mlx->w;
		tx == 0 ? ty += e->anti_a : 0;
	}
}
