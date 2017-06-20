/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 10:35:32 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:05:00 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_getnbr(char *str)
{
	int		res;

	res = 0;
	if (str != NULL && str[0] == '-')
	{
		return (-ft_getnbr(&str[1]));
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}
