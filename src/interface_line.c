/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:34:24 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/02 13:23:14 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			string_put(t_envg *e, int size[2], int color, char *str)
{
	char	*s;
	int		len;

	len = ft_strlen(str) - 1;
	s = NULL;
	if (len > 30)
	{
		s = ft_strjoin("...", str + ft_strlen(str) - 28);
		mlx_string_put(e->mlx.mlx, e->mlx.win, size[0], size[1], color, s);
		free(s);
	}
	else
		mlx_string_put(e->mlx.mlx, e->mlx.win, size[0], size[1], color, str);
}

void			add_line(char *dest, char *src, int f)
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

void			del_line(t_envg *e)
{
	int len;

	len = ft_strlen(e->line[e->pos]);
	e->line[e->pos][len - 1] = '\0';
}

static void		mlx_put_string(t_envg *e, int line, char *string)
{
	e->volet.info == 1 ? line -= 40 : 0;
	mlx_string_put(e->mlx.mlx, e->mlx.win, e->line_pos[line].w + 6,
		e->line_pos[line].h + 4, 0xffffff, string);
	if (string)
		free(string);
}

void			print_line(t_envg *e, int line, int precision)
{
	char		*string;
	int			len;
	static int	f = 1;

	len = ft_strlen(e->line[line]);
	if (e->f_key == 1)
	{
		if (f == 1)
		{
			f = 0;
			clean_str(&e->line[line], 1);
		}
		string = (len > precision) ? ft_strsub(e->line[line], len - precision,
				precision) : ft_strdup(e->line[line]);
	}
	else
	{
		f = 1;
		string = (len > precision) ? ft_strsub(e->line[line], 0,
			precision) : ft_strdup(e->line[line]);
	}
	mlx_put_string(e, line, string);
}
