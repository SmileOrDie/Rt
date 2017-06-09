/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:53:28 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] == s2[x] && s1[x] != '\0' && x < n)
	{
		if (x == n)
			return (1);
		x++;
	}
	if (s1[x] == '\0' || s2[x] == '\0' || x >= n)
		return (1);
	return (0);
}
