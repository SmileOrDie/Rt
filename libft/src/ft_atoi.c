/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:44:51 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int n;
	int signe;
	int result;

	n = 0;
	result = 0;
	signe = 1;
	while (nptr[n] == ' ' || nptr[n] == '\n' || nptr[n] == '\t'
			|| nptr[n] == '\v' || nptr[n] == '\f' || nptr[n] == '\r')
		n++;
	if (nptr[n] == '-')
	{
		signe = -1;
		n++;
	}
	else if (nptr[n] == '+')
		n++;
	while (nptr[n] > 47 && nptr[n] < 58)
	{
		result = result * 10 + (nptr[n] - 48);
		n++;
	}
	return (result * signe);
}
