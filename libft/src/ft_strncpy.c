/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/05 17:21:56 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int		d;
	int		f;

	d = 0;
	f = 0;
	while (src[d] != '\0' && (size_t)d < n)
	{
		if (src[d] == '\\')
			d++;
		else
		{
			dest[f] = src[d];
			d++;
			f++;
		}
	}
	if (src[d--] == '\0')
		while ((size_t)++d < n)
			dest[f++] = '\0';
	dest[n] = '\0';
	return (dest);
}
