/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:45:30 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/27 17:59:40 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static char		*ft_join(char *str, char *tmp)
{
	int			i;
	int			a;
	char		*tmp2;

	a = 0;
	tmp2 = NULL;
	tmp2 = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp) + 1));
	i = 0;
	while (str[i])
		tmp2[a++] = str[i++];
	i = 0;
	tmp2[a] = '.';
	a++;
	while (tmp[i] && i < 6)
		tmp2[a++] = tmp[i++];
	tmp2[a] = '\0';
	return (tmp2);
}

char			*ft_dtoa(double nb)
{
	char		*str;
	char		*tmp;
	char		*tmp2;
	double		i;
	intmax_t	v;

	str = NULL;
	tmp = NULL;
	v = (intmax_t)nb;
	i = (nb - v);
	str = ft_itoa((intmax_t)v);
	v = (i == 0) ? 0.0 : (i * 10000000) + 1;
	tmp = ft_itoa((intmax_t)v);
	tmp2 = ft_join(str, tmp);
	free(str);
	free(tmp);
	return (tmp2);
}
