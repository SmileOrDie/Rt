/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vhit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:50:06 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:20:00 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	vhit(t_vector pos, t_vector dir, double dist)
{
	t_vector c;

	c.x = pos.x + dir.x * dist;
	c.y = pos.y + dir.y * dist;
	c.z = pos.z + dir.z * dist;
	return (c);
}
