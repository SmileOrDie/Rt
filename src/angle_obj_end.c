/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_obj_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:24:46 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/10 16:24:50 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vector		ft_angle_circle(t_obj p, t_vector dir_l)
{
	(void)dir_l;
	vnorm(&p.dir);
	return (p.dir);
}

t_vector		ft_angle_square(t_obj p, t_vector dir_l)
{
	(void)dir_l;
	vnorm(&p.dir);
	return (p.dir);
}
