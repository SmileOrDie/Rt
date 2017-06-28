/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:52:37 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		x;
	int		y;
	char	*str;

	x = 0;
	y = ft_strlen(s) - 1;
	if (s == NULL)
		return (NULL);
	while (s[x] == ' ' || s[x] == '\t' || s[x] == '\n')
	{
		x++;
	}
	while ((s[y] == ' ' || s[y] == '\t' || s[y] == '\n') && y > x)
	{
		y--;
	}
	str = ft_strsub(s, x, y - x + 1);
	return (str);
}
