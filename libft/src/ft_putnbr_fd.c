/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:48:58 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	thelses(int n, int k, int fd)
{
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	while (n / k == 0)
		k /= 10;
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		while (k != 1)
		{
			ft_putchar_fd((n / k) + '0', fd);
			n = n - (n / k) * k;
			k /= 10;
			if (k == 1)
				ft_putchar_fd(n + '0', fd);
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int k;

	k = 1000000000;
	if (n == -2147483648)
		ft_putstr_fd(fd, "-2147483648", "");
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
		thelses(n, k, fd);
}
