/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_obj.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:45:36 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:09:13 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANGLE_OBJ_H
# define ANGLE_OBJ_H

typedef struct	s_aoc
{
	t_env		*e;
	t_cyl		*obj;
	t_vector	b;
	t_vector	c;
	double		n;
	double		n2;
	float		dist;
	double		tmp;
}				t_aoc;

typedef struct	s_aoco
{
	t_env		*e;
	t_cone		*obj;
	double		hypo;
	double		opp;
	double		adj;
	t_vector	b;
	t_vector	c;
	double		alpha;
	double		dist;
}				t_aoco;

#endif
