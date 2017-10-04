/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:50:57 by phmoulin          #+#    #+#             */
/*   Updated: 2017/10/04 18:10:37 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

double				get_l_pix(t_three *branch, t_l_obj *tab_light,
	t_obj *l_obj, char flag)
{
	static long int	i = 0;
	static double	coef_t = 0;

	flag == 2 ? (i = 0) : 0;
	flag ? (coef_t = 0) : 0;
	if (branch && branch->id < 0)
	{
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
		return (coef_t);
	}
	if (branch && branch->r_reflec)
		get_l_pix(branch->r_reflec, tab_light, l_obj, 0);
	if (branch && branch->r_refrac)
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
	if (branch && branch->id > 0 && branch->p_hit.coef * (1 - l_obj[branch->id -
1].ind_transp) * (1 - l_obj[branch->id - 1].ind_reflec) > 0.039 && (++i || 1))
	{
		tab_light[i - 1].id = branch->id - 1;
		tab_light[i - 1].p_hit_x = branch->p_hit.x;
		tab_light[i - 1].p_hit_y = branch->p_hit.y;
		tab_light[i - 1].p_hit_z = branch->p_hit.z;
		coef_t += branch->p_hit.coef * (1 - l_obj[branch->id - 1].ind_transp) *
		(1 - l_obj[branch->id - 1].ind_reflec);
	}
	return (coef_t);
}

void				free_branch(t_three *branch)
{
	if (branch)
	{
		free_branch(branch->r_reflec);
		free_branch(branch->r_refrac);
		free(branch);
	}
}

static void			run_rt_2(t_env *e, double *opti, int x, int y)
{
	t_vector	v_ray;

	(void)opti;
	v_ray = vrot(e->cam.up, -opti[0] / 2 + x / (double)e->win.w * opti[0], e->cam.dir);
	v_ray = vrot(vcross(e->cam.up, e->cam.dir), -opti[1] / 2 + y / (double)e->win.h * opti[1], v_ray);
	vnorm(&v_ray);
	e->begin_three = &(e->tab_three[x + y * e->win.w]);
	ft_raytracer(e, (t_ray){e->cam.eye, v_ray, 0, 1,
		(t_color2){255, 255, 255, 0}}, &(e->tab_three[x + y * e->win.w]));
}

void				*run_rt(void *env)
{
	int			y;
	int			x;
	t_env		*e;
	double		opti[6];

	e = (t_env *)env;
	opti[0] = e->win.w >= e->win.h ? e->cam.fov : e->cam.fov * (double)e->win.w / e->win.h;
	opti[1] = e->win.h >= e->win.w ? e->cam.fov : e->cam.fov * (double)e->win.h / e->win.w;
	y = 0;
	printf("eye = %f %f %f\n", e->cam.eye.x, e->cam.eye.y, e->cam.eye.z);
	while (y < e->win.h)
	{
		x = e->start;
		while (x < e->win.w)
		{
			run_rt_2(e, opti, x, y);
			x += 8;
		}
		y++;
	}
	pthread_exit(NULL);
}

t_env				*ft_create_tab_env(t_env e, int i)
{
	t_env	*tab;

	if (!(tab = (t_env *)malloc(sizeof(t_env) * i)))
		ft_error(MALLOC, "ft_create_tab_env");
	while (i--)
	{
		tab[i] = e;
		tab[i].start = i;
	}
	return (tab);
}
