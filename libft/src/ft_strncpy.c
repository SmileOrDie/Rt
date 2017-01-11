/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:53:41 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	c;
	int		d;

	c = 0;
	d = 0;
	while (src[d] != '\0' && c < n)
	{
		dest[d] = src[d];
		d++;
		c++;
	}
	if (src[d] == '\0')
	{
		while (c < n)
		{
			dest[d] = '\0';
			d++;
			c++;
		}
	}
	return (dest);
}
