/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:54:58 by phmoulin          #+#    #+#             */
/*   Updated: 2017/11/08 16:50:26 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void			mlx_put_load(t_env *e, int i)
{
	t_pos l;

	l = (t_pos){e->win.w / e->anti_a, e->win.h / e->anti_a};
	if (!e->mlx.mlx || !e->mlx.win || !e->wait_img[i] ||
		!(e->size[i].w <= l.w && e->size[i].h <= l.h))
		return ;
	e->wait = i + 1;
}

static long int		ft_launch_thread(t_env *e)
{
	t_env			*tab_env;
	long int		size_f;
	pthread_t		tab_thread[8];
	int				i;

	i = 8;
	tab_env = ft_create_tab_env(*e, i);
	while (i--)
		pthread_create(&tab_thread[i], NULL, run_rt, (void *)(&tab_env[i]));
	size_f = 0;
	while (++i < 8)
	{
		pthread_join(tab_thread[i], NULL);
		size_f += *(e->nb_obj_pix[i]);
	}
	if (!(e->tab_light = (t_l_obj *)malloc(sizeof(t_l_obj) * size_f)))
		ft_error(MALLOC, "ft_launch");
	free(tab_env);
	return (size_f);
}

static void			ft_launch_after(t_env *e)
{
	mlx_put_load(e, 1);
	get_l_tab(e);
	mlx_put_load(e, 2);
	ft_launch_calc(e, e->cl_e->cl);
	mlx_put_load(e, 3);
	get_image(e);
	e->filter_t != NULL ? e->filter_t(e, 0, 0) : 0;
	e->wait = 5;
}

static void			ft_launch_free(t_env *e, unsigned int limit)
{
	unsigned int	i;

	i = 0;
	while (i < limit)
		free_branch(e->tab_three[i++]);
	free(e->tab_three);
	free(e->tab_light);
	free(e->cl_e->color_lst);
	free(e->coef_t);
	e->b_screen = 0;
	e->flag = 0;
}

void				*ft_launch(void *env)
{
	t_env			*e;
	unsigned int	l;
	long int		size[8];
	int				i;

	e = (t_env *)env;
	i = -1;
	e->cl_e->color_lst = NULL;
	while (++i < 8)
	{
		size[i] = 0;
		e->nb_obj_pix[i] = &(size[i]);
	}
	l = e->win.w * e->win.h;
	if (!(e->coef_t = (double*)malloc(sizeof(double) * l)))
		ft_error(MALLOC, "e->coef_t => ft_launch");
	if (!(e->tab_three = (t_three **)malloc(sizeof(t_three *) * l)))
		ft_error(MALLOC, "e->tab_three => ft_launch");
	mlx_put_load(e, 0);
	if ((size[0] = ft_launch_thread(e)) > 0)
		ft_launch_after(e);
	else
		e->wait = 5;
	ft_launch_free(e, l);
	return (NULL);
}
