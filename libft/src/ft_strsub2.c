/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2017/11/09 13:30:56 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int				mask(unsigned int mask)
{
	if (mask == 0xff00)
		return (8);
	if (mask == 0xff0000)
		return (16);
	if (mask == 0xff000000)
		return (24);
	return (0);
}

unsigned char	*ft_strsub2(int const *s, size_t len, SDL_Surface *surface)
{
	unsigned char	*str;
	size_t			n;

	n = 0;
	str = malloc(sizeof(unsigned char) * len + 1);
	if (str == NULL)
		return (str);
	while (n < len)
	{
		((int*)str)[n / 4] = 0;
		str[n] = (unsigned char)((s[n / 4] & surface->format->
					Bmask) >> mask(surface->format->Bmask));
		str[n + 1] = (unsigned char)((s[n / 4] & surface->
					format->Gmask) >> mask(surface->format->Gmask));
		str[n + 2] = (unsigned char)((s[n / 4] & surface->
					format->Rmask) >> mask(surface->format->Rmask));
		str[n + 3] = (unsigned char)((s[n / 4] & surface->
					format->Amask) >> mask(surface->format->Amask));
		n += 4;
	}
	str[len] = '\0';
	return (str);
}
