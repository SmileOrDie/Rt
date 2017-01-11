/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:13:03 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/11 17:25:59 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../../includes/error.h"
# include <stdlib.h>
# include <math.h>

typedef struct	s_vector
{
	double		z;
	double		y;
	double		x;
	double		p;
}				t_vector;

t_vector		*new_v(double a, double b, double c);
t_vector		new_v2(double x, double y, double z);

t_vector		*vadd(t_vector *a, t_vector *b);
t_vector		vadd2(t_vector *a, t_vector *b);

t_vector		*vsub(t_vector *a, t_vector *b);
t_vector		vsub2(t_vector *a, t_vector *b);

t_vector		*vmult(t_vector *a, t_vector *b);
t_vector		vmult2(t_vector *a, t_vector *b);

t_vector		*vhit(t_vector *pos, t_vector *dir, double dist);
t_vector		vhit2(t_vector *pos, t_vector *dir, double dist);

double			vpscal(t_vector *a, t_vector *b);
void			vnorm(t_vector *a);

t_vector		*vmult_dbl(t_vector *a, double b);
t_vector		vmult_dbl2(t_vector *a, double b);

double			vsize(t_vector *a);

void			ft_error_var(t_vector *var, char *str, int f);

#endif
