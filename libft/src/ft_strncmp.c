/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:53:49 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		c;
	size_t	d;

	c = 0;
	d = 0;
	while (s1[c] != '\0' && d < n && s2[c] != '\0')
	{
		if (s1[c] - s2[c] != 0)
			return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
		c++;
		d++;
	}
	if (d == n)
		return ((int)((unsigned char)s1[c - 1] - (unsigned char)s2[c - 1]));
	return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
}
