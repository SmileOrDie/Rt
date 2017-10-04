/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:54:58 by phmoulin          #+#    #+#             */
/*   Updated: 2017/10/04 17:48:51 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

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
	get_l_tab(e);
	ft_launch_calc(e, e->cl_e->cl);
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
	if ((size[0] = ft_launch_thread(e)) > 0)
		ft_launch_after(e);
	else
		e->wait = 5;
	ft_launch_free(e, l);
	return (NULL);
}
