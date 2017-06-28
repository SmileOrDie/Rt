/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_object2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 11:35:38 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 11:35:52 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_vector	ft_angle_sphere(t_obj s, t_vector hit)
{
	t_vector		pho;

	pho = vsub(hit, s.pos);
	vnorm(&pho);
	return (pho);
}
