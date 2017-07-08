/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:48:30 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/08 12:07:06 by pde-maul         ###   ########.fr       */
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

void			boucle2(t_norme11 n)
{
	vnorm(&n.v_ray);
	n.e->begin_three = &(n.e->tab_three[n.x + n.y * n.e->mlx->w]);
	ft_raytracer(n.e, n.e->cam->eye, n.v_ray, 0, 1, (t_color2){255, 255, 255,\
		0}, &(n.e->tab_three[n.x + n.y * n.e->mlx->w]));
}

void			*boucle(void *env)
{
	t_norme11	n;

	n.e = (t_env *)env;
	n.y = 0;
	while (n.y < n.e->mlx->h)
	{
		n.x = n.e->start;
		while (n.x < n.e->mlx->w)
		{
			n.p_cam = new_v(n.e->cam->l.x + n.e->cam->u.x * n.x * (n.e->cam->w /
				n.e->mlx->w) + n.e->cam->up.x * n.y * (n.e->cam->h / \
				n.e->mlx->h), n.e->cam->l.y + n.e->cam->u.y * n.x * \
				(n.e->cam->w / n.e->mlx->w) + n.e->cam->up.y * n.y * \
				(n.e->cam->h / n.e->mlx->h), n.e->cam->l.z + n.e->cam->u.z * \
				n.x * (n.e->cam->w / n.e->mlx->w) + n.e->cam->up.z * n.y * \
				(n.e->cam->h / n.e->mlx->h));
			n.v_ray = vsub(n.p_cam, n.e->cam->eye);
			boucle2(n);
			n.x += 3;
		}
		n.y++;
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
