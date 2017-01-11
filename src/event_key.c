/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:07:08 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		keypress(int key, t_env *e)
{
	(void)e;
	if (key == ESC)
		exit(1);
	return (1);
}

int		redcross(t_env *e)
{
	(void)e;
	exit(1);
	return (1);
}
