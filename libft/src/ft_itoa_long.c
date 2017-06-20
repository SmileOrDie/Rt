/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:46:30 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long int		ft_calc_long(long int n, int *len)
{
	long int	k;

	k = n;
	while (k)
	{
		k /= 10;
		len[0]++;
	}
	if (n < 0)
	{
		len[1]++;
		n *= -1;
	}
	return (n);
}

void			fln_long(char *str, int *len)
{
	if (len[1])
		str[0] = '-';
	str[len[0] + len[1]] = '\0';
}

char			*jedoismlloc_long(long int n)
{
	char	*st;
	int		i;

	i = 18;
	st = NULL;
	st = malloc(sizeof(char) * 21);
	if (n == 0)
	{
		st[1] = '\0';
		st[0] = '0';
	}
	else
	{
		st[0] = '-';
		st[19] = '8';
		st[20] = '\0';
		n /= -10;
		while (n)
		{
			st[i] = n % 10 + '0';
			n /= 10;
			i--;
		}
	}
	return (st);
}

char			*ft_itoa_long(long int n)
{
	int		len[2];
	char	*str;

	len[0] = 0;
	len[1] = 0;
	if (n == 0 || n == (long)(-0x7fffffffffffffffL - 1))
	{
		str = jedoismlloc_long(n);
		return (str);
	}
	n = ft_calc_long(n, len);
	if (!(str = malloc(len[0] * sizeof(char) + 1 + len[1])))
		return (NULL);
	fln_long(str, len);
	while (n)
	{
		str[len[0] - 1 + len[1]] = n % 10 + '0';
		n /= 10;
		len[0]--;
	}
	return (str);
}
