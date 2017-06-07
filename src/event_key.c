/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/19 16:57:46 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"


int		keypress(int key, t_envg *e)
{
	(void)e;
	// printf("%i\n", key);
	if (key == ESC)
	{
		// ft_exit3(e->e);
		ft_exit(e);
	}
	else if (key == 123)
	{
		e->e->cam->eye.x += 10;
		e->e->cam->l_at.x += 10;
	// 	e->e->move = 1;
	// 	ft_launch_calc(e->e, e->e->cl);
	}
	else if (key == 124)
	{
		e->e->cam->eye.x -= 10;
		e->e->cam->l_at.x -= 10;
	// 	e->e->move = 1;
	// 	ft_launch_calc(e->e, e->e->cl);
	}
	else if (key == 125)
	{
		e->e->cam->eye.y += 10;
		e->e->cam->l_at.y += 10;
	// 	e->e->move = 1;
	// 	ft_launch_calc(e->e, e->e->cl);
	}
	else if (key == 126)
	{
		e->e->cam->eye.y -= 10;
		e->e->cam->l_at.y -= 10;
	// 	e->e->move = 1;
	// 	ft_launch_calc(e->e, e->e->cl);
	}
	return (1);
}

int		redcross(t_env *e)
{
	(void)e;
	// ft_exit3(e);
	exit(1);
	return (1);
}
