/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:50:39 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		x;
	char	*copie;

	x = 0;
	i = ft_strlen(s);
	if ((copie = malloc(sizeof(char) * (i + 1))) == NULL)
		return (0);
	while (x != i)
	{
		copie[x] = s[x];
		x++;
	}
	copie[x] = '\0';
	return (copie);
}
