/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:55:20 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/19 16:58:13 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void		ft_exit(char *error, char *in)
{
	write(2, error, ft_strlen(error));
	write(2, in, ft_strlen(in));
	write(2, "\n", 1);
	exit(-1);
}

static int		is_double(char *str)
{
	int v;

	if (!str)
		return (0);
	if (*str == '-')
		str++;
	v = 0;
	while (*str)
	{
		if ((*str < '0' || *str > '9') && (*str != '.' && *str != ','))
			return (0);
		if (*str == '.' || *str == ',')
			v++;
		if (v > 1)
			return (0);
		str++;
	}
	return (1);
}

double			ft_atof(char *str)
{
	double		n;
	int			i;
	int			k;
	int			signe;

	i = 0;
	n = 0;
	k = 0;
	signe = 1;
	if (!is_double(str))
		ft_exit("error value ft_atof() : ", str);
	signe = (str[i] == '-') ? -signe : signe;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + (str[i++] - 48);
		if (str[i] == '.' || str[i] == ',')
			k = i++;
	}
	while (k != 0 && str[++k])
		signe = signe * 10;
	return (n / signe);
}
