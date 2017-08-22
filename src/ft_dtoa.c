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

// static char		*ft_join(char *str, char *tmp)
// {
// 	int			i;
// 	int			a;
// 	int			x;
// 	char		*tmp2;

// 	x = 0;
// 	a = 0;
// 	tmp2 = NULL;
// 	tmp2 = (char *)malloc(sizeof(char) * (ft_strlen(str) + 8));
// 	i = 0;
// 	while (str[i])
// 		tmp2[a++] = str[i++];
// 	i = 0;
// 	tmp2[a] = '.';
// 	a++;
// 	while (ft_strlen(tmp) + x < 7)
// 	{
// 		tmp2[a + x] = '0';
// 		x++;
// 	}
// 	a = a + x;
// 	while (tmp[i] && i < 6)
// 		tmp2[a++] = tmp[i++];
// 	tmp2[a] = '\0';
// 	return (tmp2);
// }

// char			*ft_dtoa(double nb)
// {
// 	char		*str;
// 	char		*tmp;
// 	char		*tmp2;
// 	double		i;
// 	intmax_t	v;

// 	str = NULL;
// 	tmp = NULL;
// 	v = (intmax_t)nb;
// 	i = (nb - v);
// 	str = ft_itoa((intmax_t)v);
// 	v = (i == 0.0) ? 0.0 : (i * 10000000) + 1;
// 	tmp = ft_itoa((intmax_t)v);
// 	tmp2 = ft_join(str, tmp);
// 	free(str);
// 	free(tmp);
// 	printf("%s\n", tmp2);
// 	return (tmp2);
// }

char			*ft_dtoa(double nb)
{
	int		ent;
	char	*part_ent;
	char	part_dec[7];
	char	*rez;
	int		x;

	x = 0;
	ent = nb;
	part_ent = ft_itoa(ent);
	rez = ft_strjoin(part_ent, ".");
	free(part_ent);
	nb = nb - (int)nb;
	nb = nb < 0.0 ? -nb : (nb);
	part_dec[6] = '\0';
	while (x < 6)
	{
		nb *= 10;
		printf("nb = %f\n", nb);
		part_dec[x] = '0' + (char)((int)nb);
		nb = nb - (int)nb;
		x++;
	}
	part_ent = ft_strjoin(rez, part_dec);
	free(rez);
	return (part_ent);
}