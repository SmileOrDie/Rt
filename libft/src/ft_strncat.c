/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:53:55 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, char *src, size_t n)
{
	int		c;
	size_t	d;
	int		f;

	d = 0;
	c = 0;
	f = 0;
	while (dest[c] != '\0')
		c++;
	while (src[f] != '\0' && n > d)
	{
		dest[c] = src[f];
		c++;
		d++;
		f++;
	}
	dest[c] = '\0';
	return (dest);
}
