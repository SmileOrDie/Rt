/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:48:54 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	thelse(int n, int k)
{
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	while (n / k == 0)
		k /= 10;
	if (n < 10)
		ft_putchar(n + '0');
	else
	{
		while (k != 1)
		{
			ft_putchar((n / k) + '0');
			n = n - (n / k) * k;
			k /= 10;
			if (k == 1)
				ft_putchar(n + '0');
		}
	}
}

void	ft_putnbr(int n)
{
	int k;

	k = 1000000000;
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n == 0)
		ft_putchar('0');
	else
		thelse(n, k);
}
