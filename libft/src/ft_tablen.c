/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:30:04 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:08:38 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_tablen(char ***tab, int f)
{
	int i;

	i = 0;
	while ((*tab)[i])
	{
		if (f == 1)
			free((*tab)[i]);
		i++;
	}
	if (f == 1)
	{
		free(*tab);
		*tab = NULL;
	}
	return (i);
}
