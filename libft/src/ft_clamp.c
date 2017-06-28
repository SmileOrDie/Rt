/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:09:57 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:11:06 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

double		ft_clamp_min(double a, double b)
{
	double r;

	r = (a < b) ? b : a;
	return (r);
}

double		ft_clamp_max(double a, double b)
{
	double r;

	r = (a > b) ? b : a;
	return (r);
}

double		ft_clamp(double a, double b, double c)
{
	double r;

	r = (a < b) ? b : a;
	r = (a > c) ? c : a;
	return (r);
}
