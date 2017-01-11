/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:42:12 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:08:26 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_error(char *error, char *in)
{
	write(2, error, ft_strlen(error));
	write(2, in, ft_strlen(in));
	write(2, "\n", 1);
	exit(-1);
}

void			ft_error_var(t_vector *v, char *str, int f)
{
	if (f == 1)
	{
		if (v->x <= 0 || v->y <= 0 || v->z <= 0)
			ft_error("vector can't be NULL or negatif : ", str);
	}
	else
	{
		if (v->x < 0 || v->y < 0 || v->z < 0)
			ft_error("vector can't be negatif : ", str);
	}
}
