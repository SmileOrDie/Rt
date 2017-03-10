/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesprog <ldesprog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/03/09 18:46:05 by ldesprog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_exit(t_env *e)
{
	clReleaseKernel(e->cl->kernel);
	clReleaseProgram(e->cl->kernel_program);
	clReleaseCommandQueue(e->cl->command_queue);
	clReleaseMemObject(e->cl->data);
	clReleaseMemObject(e->cl->obj);
	clReleaseMemObject(e->cl->light);
	clReleaseMemObject(e->cl->env);
	clReleaseMemObject(e->cl->mlx);
	clReleaseMemObject(e->cl->cam);
	clReleaseContext(e->cl->context);
	exit(0);
}

int		keypress(int key, t_env *e)
{
	(void)e;
	// printf("%i\n", key);
	if (key == ESC)
		ft_exit(e);
	else if (key == 123)
	{
		e->cam->eye.x += 10;
		e->cam->l_at.x += 10;
		e->move = 1;
		ft_launch_calc(e, e->cl);
	}
	else if (key == 124)
	{
		e->cam->eye.x -= 10;
		e->cam->l_at.x -= 10;
		e->move = 1;
		ft_launch_calc(e, e->cl);
	}
	else if (key == 125)
	{
		e->cam->eye.y += 10;
		e->cam->l_at.y += 10;
		e->move = 1;
		ft_launch_calc(e, e->cl);
	}
	else if (key == 126)
	{
		e->cam->eye.y -= 10;
		e->cam->l_at.y -= 10;
		e->move = 1;
		ft_launch_calc(e, e->cl);
	}
	return (1);
}

int		redcross(t_env *e)
{
	(void)e;
	ft_exit(e);
	return (1);
}
