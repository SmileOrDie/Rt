/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:07:22 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/27 16:41:26 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static	void	ft_cal(char *str, double *i, int *v, int *s)
{
	while (str[*v] >= 48 && str[*v] <= 57)
	{
		if (str[*v] >= 48 && str[*v] <= 57)
			*i = *i * 10 + (str[*v] - '0');
		*v += 1;
		if (str[*v] == '.')
		{
			*s = *v + 1;
			*v += 1;
		}
	}
	if (*s > 0)
	{
		*s = *v - *s;
		while (*s > 0)
		{
			*i = *i / 10;
			*s -= 1;
		}
	}
}

double			ft_atod(char *str)
{
	int		v;
	int		s;
	int		neg;
	double	i;

	neg = 0;
	s = 0;
	i = 0;
	v = 0;
	while (str[v] && (str[v] == ' ' || str[v] == '\v' || str[v] == '\n'
				|| str[v] == '\f' || str[v] == '\t' || str[v] == '\r'))
		v++;
	if (str[v] == '-')
	{
		neg = 1;
		v++;
	}
	else if (str[v] == '+')
		v++;
	ft_cal(str, &i, &v, &s);
	return ((neg == 1 && i != 0) ? -i : i);
}
