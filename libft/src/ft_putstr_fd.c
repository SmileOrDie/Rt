/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:49:09 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_fd(int fd, ...)
{
	int		i;
	char	*str;
	va_list	ap;

	va_start(ap, fd);
	str = va_arg(ap, char*);
	while (str != NULL)
	{
		i = 0;
		while (str[i] != '\0')
		{
			write(fd, &(str[i]), 1);
			i++;
		}
		str = va_arg(ap, char*);
	}
	va_end(ap);
}
