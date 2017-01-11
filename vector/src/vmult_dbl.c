/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmult_dbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:40 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:21:49 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	*vmult_dbl(t_vector *a, double b)
{
	t_vector *ret;

	ret = new_v(a->x * b, a->y * b, a->z * b);
	return (ret);
}

t_vector	vmult_dbl2(t_vector *a, double b)
{
	t_vector ret;

	ret = new_v2(a->x * b, a->y * b, a->z * b);
	return (ret);
}
