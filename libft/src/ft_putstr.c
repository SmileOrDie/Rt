/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:49:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr(char const *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}
