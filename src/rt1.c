/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:48:30 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 11:52:11 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

t_env			*ft_create_tab_env(t_env e)
{
	t_env	*tab;

	tab = (t_env *)malloc(sizeof(t_env) * 3);
	tab[0] = e;
	tab[1] = e;
	tab[2] = e;
	tab[0].start = 0;
	tab[1].start = 1;
	tab[2].start = 2;
	return (tab);
}

double			get_l_pix(t_three *branch, t_l_obj *tab_light, t_obj *l_obj, \
	char flag)
{
	static long int	i = 0;
	static double	coef_t = 0;

	flag == 2 ? (i = 0) : 0;
	flag ? (coef_t = 0) : 0;
	if (branch && branch->r_reflec)
		get_l_pix(branch->r_reflec, tab_light, l_obj, 0);
	if (branch && branch->r_refrac)
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
	if (branch && branch->p_hit.coef * (1 - l_obj[branch->id].ind_transp) * \
	(1 - l_obj[branch->id].ind_reflec) > 0.04)
	{
		tab_light[i].id = branch->id;
		tab_light[i].p_hit_x = branch->p_hit.x;
		tab_light[i].p_hit_y = branch->p_hit.y;
		tab_light[i].p_hit_z = branch->p_hit.z;
		coef_t += branch->p_hit.coef * (1 - l_obj[branch->id].ind_transp) * \
		(1 - l_obj[branch->id].ind_reflec);
		i++;
	}
	return (coef_t);
}

void			*boucle(void *env)
{
	int			y;
	int			x;
	t_vector	p_cam;
	t_vector	v_ray;
	t_env		*e;

	e = (t_env *)env;
	y = 0;
	while (y < e->mlx->h)
	{
		x = e->start;
		while (x < e->mlx->w)
		{
			p_cam = new_v(e->cam->l.x + e->cam->u.x * x * (e->cam->w / \
				e->mlx->w) + e->
				cam->up.x * y * (e->cam->h / e->mlx->h), e->cam->l.y + \
				e->cam->u.y *
				x * (e->cam->w / e->mlx->w) + e->cam->up.y * y * (e->cam->h / \
					e->mlx->h)
				, e->cam->l.z + e->cam->u.z * x * (e->cam->w / e->mlx->w) + e->
				cam->up.z * y * (e->cam->h / e->mlx->h));
			v_ray = vsub(p_cam, e->cam->eye);
			vnorm(&v_ray);
			e->begin_three = &(e->tab_three[x + y * e->mlx->w]);
			ft_raytracer(e, e->cam->eye, v_ray, 0, 1, (t_color2){255, 255, 255,\
				0}, &(e->tab_three[x + y * e->mlx->w]));
			x += 3;
		}
		y++;
	}
	pthread_exit(NULL);
}

void			free_branch(t_three *branch)
{
	if (branch)
	{
		free_branch(branch->r_reflec);
		free_branch(branch->r_refrac);
		free(branch);
	}
}

void			get_l_tab(t_env *e)
{
	int		i;
	char	flag;

	i = 0;
	flag = 2;
	while (i < e->mlx->h * e->mlx->w)
	{
		e->coef_t[i] = get_l_pix(e->tab_three[i], e->tab_light, e->l_obj, flag);
		i++;
		flag = 1;
	}
}
