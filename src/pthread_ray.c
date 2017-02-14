/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:54:22 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/24 12:51:23 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		init_limit(t_limit *l, int xend, int y, int yend)
{
	l->y_start = 0;
	l->y_end = xend;
	l->x_start = y;
	l->x_end = yend;
}

static void		init_thread(t_env *e, t_env *cp, int size)
{
	int 		i;
	int 		part;

	part = e->mlx->w / size;
	i = 0;
	while (i < size)
	{
		init_limit(&(cp[i]).l, e->mlx->h, i * part, part + i * part);
		(cp[i]).mlx = e->mlx;
		(cp[i]).cam = e->cam;
		(cp[i]).light = e->light;
		(cp[i]).d_light = e->d_light;
		(cp[i]).l_obj = e->l_obj;
		(cp[i]).obj = e->obj;
		(cp[i]).amb = e->amb;
		(cp[i]).c_hit = e->c_hit;
		(cp[i]).flag = 0;
		(cp[i]).r = 0;
		(cp[i]).g = 0;
		(cp[i]).b = 0;
		(cp[i]).angle = 0;		
		i++;
	}
}

void			pthread_ray(t_env *env)
{
	pthread_t	threads[env->nb_thread];
	int			err;
	int 		nb_t;
	t_env 		*e;

	nb_t = 0;
	if (!(e = (t_env *)malloc(sizeof(t_env) * (env->nb_thread + 1))))
		ft_error(MALLOC, "(=> multi-env)-(pthread_ray.c)");
	init_thread(env, e, env->nb_thread);
	while (nb_t < env->nb_thread)
	{
		err = pthread_create(&(threads[nb_t]), NULL, start_ray, &(e[nb_t]));
		if (err)
			ft_error(THREAD_C_E, ft_itoa(err));
		nb_t++;
	}
	nb_t = -1;
	while (++nb_t < env->nb_thread)
		pthread_join(threads[nb_t], NULL);
	// mlx_put_image_to_window(env->mlx->mlx, env->mlx->win, env->mlx->img, 0, 0);
	nb_t = 0;
	while (nb_t < env->nb_thread)
	{
		err = pthread_create(&(threads[nb_t]), NULL, ft_aliasing, &(e[nb_t]));
		if (err)
			ft_error(THREAD_C_E, ft_itoa(err));
		nb_t++;
	}
	nb_t = -1;
	while (++nb_t < env->nb_thread)
		pthread_join(threads[nb_t], NULL);
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img4, 0, 0);;
}
