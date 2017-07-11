/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:53:01 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/10 18:28:08 by pde-maul         ###   ########.fr       */
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
	// n'etait pas la ce qui suit
	if (branch->id < 0)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		pixel = add_color(pixel, color_ray);
		return (pixel);
	}
	//
	if (branch->r_reflec)
	{
		color_ray = get_pixel(branch->r_reflec, pixel, e, 0, coef_t);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id - 1].ind_reflec);
		pixel = add_color(pixel, color_ray);
	}
	// if (branch->r_refrac)
	// {
	// 	color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
	// 	color_ray.r = color_ray.r * (branch->c_origin.r / 255.0);
	// 	color_ray.g = color_ray.g * (branch->c_origin.g / 255.0);
	// 	color_ray.b = color_ray.b * (branch->c_origin.b / 255.0);
	// 	color_ray = mult_color(color_ray, branch->p_hit.coef *  e->l_obj[branch->id].ind_transp * (1 - e->l_obj[branch->id].ind_reflec));
	// 	pixel = add_color(pixel, color_ray);
	// }
	if (branch->r_refrac)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		color_ray.r = color_ray.r * (branch->c_origin.r / 255.0);
		color_ray.g = color_ray.g * (branch->c_origin.g / 255.0);
		color_ray.b = color_ray.b * (branch->c_origin.b / 255.0);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id - 1].ind_transp * (1 - e->l_obj[branch->id - 1].ind_reflec));
		pixel = add_color(pixel, color_ray);
	}
	// if (branch->p_hit.coef * (1 - e->l_obj[branch->id].ind_transp) * \
	// (1 - e->l_obj[branch->id].ind_reflec) > 0.04)
	// {
	// 	color_ray = mult_color((t_color2){(unsigned char)e->color_lst[i].r, \
	// 		(unsigned char)e->color_lst[i].g, \
	// 		(unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef * \
	// 		(1 - e->l_obj[branch->id].ind_transp) * \
	// 		(1 - e->l_obj[branch->id].ind_reflec) / coef_t);
	// 	pixel = add_color(pixel, color_ray);
	// 	i++;
	// }
	if (branch->p_hit.coef * (1 - e->l_obj[branch->id - 1].ind_transp) * (1 - \
		e->l_obj[branch->id - 1].ind_reflec) > 0.039)
	{
		color_ray = e->l_obj[branch->id - 1].negatif > 0 ? \
		mult_color((t_color2){(unsigned char)e->color_lst[i].r, (unsigned \
		char)e->color_lst[i].g, (unsigned char)e->color_lst[i].b, 0}, \
		branch->p_hit.coef / coef_t) : mult_color((t_color2){(unsigned \
		char)e->color_lst[i].r, (unsigned char)e->color_lst[i].g, \
		(unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef * (1 - \
		e->l_obj[branch->id - 1].ind_transp) * (1 - e->l_obj[branch->id - \
		1].ind_reflec) / coef_t);
		pixel = add_color(pixel, color_ray);
		i++;
	}
	return (pixel);
}

int				get_image3(t_env *e, t_norme12 *n)
{
	n->color[0] += n->img[n->tx * 4 + n->ty * e->mlx->w * 4 + 2 + n->tmpy * \
	e->mlx->w * 4 + n->tmpx * 4];
	n->color[1] += n->img[n->tx * 4 + n->ty * e->mlx->w * 4 + 1 + n->tmpy * \
	e->mlx->w * 4 + n->tmpx * 4];
	n->color[2] += n->img[n->tx * 4 + n->ty * e->mlx->w * 4 + 0 + n->tmpy * \
	e->mlx->w * 4 + n->tmpx * 4];
	return (n->tmpy);
}

void			get_image2(t_env *e, t_norme12 n)
{
	while (n.i < e->mlx->h * e->mlx->w / e->anti_a / e->anti_a)
	{
		n.tmpy = 0;
		n.color[0] = 0;
		n.color[1] = 0;
		n.color[2] = 0;
		while (n.tmpy < e->anti_a)
		{
			n.tmpx = 0;
			while (n.tmpx < e->anti_a)
			{
				n.tmpy = get_image3(e, &n);
				n.tmpx++;
			}
			n.tmpy++;
		}
		e->mlx->data[n.i * 4 + 0] = n.color[2] / e->anti_a / e->anti_a;
		e->mlx->data[n.i * 4 + 1] = n.color[1] / e->anti_a / e->anti_a;
		e->mlx->data[n.i * 4 + 2] = n.color[0] / e->anti_a / e->anti_a;
		n.i++;
		n.tx = (n.tx + e->anti_a) % e->mlx->w;
		n.tx == 0 ? n.ty += e->anti_a : 0;
	}
}

void			get_image(t_env *e)
{
	t_norme12	n;

	n.flag = 1;
	n.i = 0;
	n.img = malloc(e->mlx->h * e->mlx->w * 4);
	while (n.i < e->mlx->h * e->mlx->w)
	{
		n.pixel = get_pixel(e->tab_three[n.i], (t_color2){0, 0, 0, 0}, e->cl_e,\
		n.flag, e->coef_t[n.i]);
		n.img[n.i * 4 + 2] = n.pixel.r;
		n.img[n.i * 4 + 1] = n.pixel.g;
		n.img[n.i * 4 + 0] = n.pixel.b;
		n.i++;
		n.flag = 0;
	}
	n.i = 0;
	n.tx = 0;
	n.ty = 0;
	get_image2(e, n);
}
