/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:34:24 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/14 18:37:55 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void	add_line(char *dest, char *src, int f)
{
	int d;

	d = ft_strlen(dest);
	if (f == 1 && (isdigit(*src) ||
		(ft_strchr(dest, '.') == NULL && *src == '.') ||
		(*src == '-' && d == 0)))
	{
		dest[d] = *src;
		dest[d + 1] = '\0';
	}
	else if (f == 0)
	{
		dest[d] = *src;
		dest[d + 1] = '\0';
	}
}

void	del_line(t_envg *e)
{
	int len;

	len = ft_strlen(e->line[e->pos]);
	e->line[e->pos][len - 1] = '\0';
}

void	print_line(t_envg *e, int line, int precision)
{
	char *string;
	int len;

	string = NULL;
	len = ft_strlen(e->line[line]);
	if (e->f_key == 1)
	{
		if (len > precision)
			string = ft_strsub(e->line[line], len - precision, precision);
		else
			string = ft_strdup(e->line[line]);
	}
	else
	{
		if (len > precision)
			string = ft_strsub(e->line[line], 0, precision);
		else
			string = ft_strdup(e->line[line]);
	}
	e->volet.info == 1 ? line -= 40 : 0;
	mlx_string_put(e->mlx->mlx, e->mlx->win, e->line_pos[line].w + 6,
		e->line_pos[line].h + 4, 0xffffff, string);
	if (string)
		free(string);
}
