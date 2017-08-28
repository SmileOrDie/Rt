/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:52:50 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/28 18:53:42 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void				get_l_tab(t_env *e)
{
	int		i;
	char	flag;

	i = 0;
	flag = 2;
	while (i < e->win.h * e->win.w)
	{
		e->coef_t[i] = get_l_pix(e->tab_three[i], e->tab_light, e->l_obj, flag);
		i++;
		flag = 1;
	}
}

static void			get_pix_refrac(t_env_cl *e, t_color2 *color_ray,
	t_three *branch, t_color2 *pixel)
{
	color_ray->r = color_ray->r * (branch->c_origin.r / 255.0);
	color_ray->g = color_ray->g * (branch->c_origin.g / 255.0);
	color_ray->b = color_ray->b * (branch->c_origin.b / 255.0);
	*color_ray = mult_color(*color_ray, branch->p_hit.coef * e->l_obj[branch->id
		- 1].ind_transp * (1 - e->l_obj[branch->id - 1].ind_reflec));
	*pixel = add_color(*pixel, *color_ray);
}

static void			get_pix_reflec(t_env_cl *e, t_color2 *color_ray,
	t_three *branch, t_color2 *pixel)
{
	*color_ray = mult_color(*color_ray, branch->p_hit.coef *
		e->l_obj[branch->id - 1].ind_reflec);
	*pixel = add_color(*pixel, *color_ray);
}

static int			get_pixel_neg_color(t_color2 *pix, t_env_cl *e,
	t_three *branch, t_g_pix n)
{
	t_color2		color_ray;

	color_ray = e->l_obj[branch->id - 1].negatif > 0 ?
	mult_color((t_color2){(unsigned char)e->color_lst[n.i].r,
	(unsigned char)e->color_lst[n.i].g, (unsigned char)e->color_lst[n.i].b, 0},
	branch->p_hit.coef / n.coef) : mult_color((t_color2){(unsigned char)
	e->color_lst[n.i].r, (unsigned char)e->color_lst[n.i].g, (unsigned char)
	e->color_lst[n.i].b, 0}, branch->p_hit.coef * (1 - e->l_obj[branch->id -
	1].ind_transp) * (1 - e->l_obj[branch->id - 1].ind_reflec) / n.coef);
	*pix = add_color(*pix, color_ray);
	return (1);
}

t_color2			get_pixel(t_three *bra, t_color2 pix, t_env_cl *e,
	t_g_pix n)
{
	t_color2		color_ray;
	static int		i = 0;

	n.flag ? (i = 0) : 0;
	if (!bra)
		return ((t_color2){0, 0, 0, 0});
	if (bra->id < 0)
	{
		color_ray = get_pixel(bra->r_refrac, pix, e, (t_g_pix){0, n.coef, i});
		return (pix = add_color(pix, color_ray));
	}
	if (bra->r_reflec)
	{
		color_ray = get_pixel(bra->r_reflec, pix, e, (t_g_pix){0, n.coef, i});
		get_pix_reflec(e, &color_ray, bra, &pix);
	}
	if (bra->r_refrac)
	{
		color_ray = get_pixel(bra->r_refrac, pix, e, (t_g_pix){0, n.coef, i});
		get_pix_refrac(e, &color_ray, bra, &pix);
	}
	if (bra->p_hit.coef * (1 - e->l_obj[bra->id - 1].ind_transp) *
		(1 - e->l_obj[bra->id - 1].ind_reflec) > 0.039)
		i += get_pixel_neg_color(&pix, e, bra, (t_g_pix){0, n.coef, i});
	return (pix);
}
