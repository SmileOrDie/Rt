/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2017/10/02 18:12:48 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;

	n = 0;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (str);
	if ((size_t)start >= ft_strlen(s))
	{
		str[0] = '\0';
		return (str);
	}
	if (!s)
		return (str);
	while (n < len)
	{
		str[n] = s[start + n];
		n++;
	}
	str[len] = '\0';
	return (str);
}
