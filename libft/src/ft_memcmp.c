/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:47:26 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*st;
	int				x;
	size_t			v;

	str = (unsigned char*)s1;
	st = (unsigned char*)s2;
	x = 0;
	v = 0;
	while (n--)
	{
		if (str[x] != st[x])
			return ((int)((unsigned char)str[x] - (unsigned char)st[x]));
		x++;
		v++;
	}
	return (0);
}
