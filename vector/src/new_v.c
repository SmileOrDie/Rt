/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:05:18 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:17:38 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	new_v(double x, double y, double z)
{
	t_vector new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
