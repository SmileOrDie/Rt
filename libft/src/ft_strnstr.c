/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:53:17 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int x;
	unsigned int y;

	x = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[x] != '\0' && (size_t)x < n)
	{
		y = 0;
		while (s2[y] == s1[x + y] && (size_t)(x + y) < n)
		{
			if (s2[y + 1] == '\0')
				return ((char*)(s1 + x));
			y++;
		}
		x++;
	}
	return (NULL);
}
