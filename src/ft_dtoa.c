/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 16:45:30 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/22 19:28:21 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

char			*ft_dtoa(double nb)
{
	int			ent;
	char		*part_ent;
	char		part_dec[7];
	char		*rez;
	int			x;

	x = -1;
	ent = nb;
	rez = nb < 0 ? ft_itoa(-ent) : ft_itoa(ent);
	part_ent = nb < 0 ? ft_strjoin("-", rez) : ft_strdup(rez);
	free(rez);
	nb = nb < 0 ? -nb : nb;
	rez = ft_strjoin(part_ent, ".");
	free(part_ent);
	nb = nb - (int)nb;
	part_dec[6] = '\0';
	while (++x < 6)
	{
		nb *= 10;
		part_dec[x] = '0' + (char)((int)nb);
		nb = nb - (int)nb;
	}
	part_ent = ft_strjoin(rez, part_dec);
	free(rez);
	return (part_ent);
}
