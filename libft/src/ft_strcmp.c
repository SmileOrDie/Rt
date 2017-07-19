/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/05 15:33:58 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int c;

	c = 0;
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == NULL && s2 == NULL)
			return (0);
		return (-1);
	}
	while (s1[c] != '\0' && s2[c] != '\0')
	{
		if (s1[c] - s2[c] != 0)
			return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
		c++;
	}
	return ((int)((unsigned char)s1[c] - (unsigned char)s2[c]));
}
