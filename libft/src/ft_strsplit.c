/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/09 19:12:31 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	creationdutab(char const *s, char c, int *dim)
{
	int count;
	int nb;

	count = 0;
	dim[1] = -1;
	dim[0] = 0;
	while (s[count])
	{
		nb = 0;
		while (s[count] == c)
			count++;
		s[count] ? dim[0]++ : 0;
		while (s[count] && s[count] != c)
		{
			nb++;
			if (nb > dim[1])
				dim[1] = nb;
			count++;
		}
	}
}

void	final(char const *s, char c, char **str)
{
	int n;
	int x;
	int y;

	x = 0;
	y = 0;
	n = 0;
	while (s[n])
	{
		if (s[n] != c)
		{
			while (s[n] != c && s[n])
			{
				str[y][x] = s[n];
				n++;
				x++;
			}
			str[y][x] = '\0';
			x = 0;
			y++;
		}
		else
			n++;
	}
	str[y] = NULL;
}

char	**ft_strsplit(char const *s, char c)
{
	int		dim[2];
	char	**str;
	int		mots;

	if (s == NULL)
		return (NULL);
	creationdutab(s, c, dim);
	mots = 0;
	str = (char**)malloc(sizeof(char*) * (dim[0] + 1));
	if (str == NULL)
		return (NULL);
	while (mots < dim[0])
	{
		str[mots] = (char*)malloc(sizeof(char) * (dim[1] + 1));
		if (str[mots] == NULL)
			return (NULL);
		mots++;
	}
	final(s, c, str);
	return (str);
}
