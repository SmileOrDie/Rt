/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_obj.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:25:37 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:09:23 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_OBJ_H
# define INTER_OBJ_H

typedef struct	s_ioc
{
	double		alpha;
	t_vector	origin;
	t_vector	tmp1;
	t_vector	tmp2;
	t_vector	dir_dir;
	t_vector	o_dir;
}				t_ioc;

typedef struct	s_iocy
{
	double		t0;
	double		t1;
	double		a;
	double		b;
	double		c;
	t_vector	dp;
	t_vector	tmp;
	t_vector	tmp2;
}				t_iocy;

typedef	struct	s_ios
{
	t_vector	dist_s;
	double		b;
	double		d;
	double		t0;
	double		t1;
	double		a;
	int			result;
}				t_ios;

#endif
