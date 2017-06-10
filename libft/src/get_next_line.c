/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 14:56:01 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:08:53 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void				ft_get1(int ret, char *buf, char **tmp)
{
	char			*tmp2;

	buf[ret] = '\0';
	tmp2 = *tmp;
	*tmp = ft_strjoin(tmp2, buf);
	ft_strdel(&tmp2);
}

void				ft_get2(char **line, char **tmp)
{
	char			*tmp2;
	size_t			len;

	len = ft_strchr(*tmp, '\n') - *tmp;
	*line = ft_strsub(*tmp, 0, len);
	tmp2 = *tmp;
	*tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	ft_strdel(&tmp2);
}

int					get_next_line(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static char		*tmp;

	if (!line || fd < 0)
		return (-1);
	if (!tmp)
		tmp = ft_strnew(0);
	ret = 0;
	while ((ft_strchr(tmp, '\n')) == NULL
		&& (ret = read(fd, buf, BUFF_SIZE)) > 0)
		ft_get1(ret, buf, &tmp);
	if (ret == -1)
		return (-1);
	if (ret == 0 && ft_strchr(tmp, '\n') == NULL)
	{
		*line = tmp;
		tmp = NULL;
		return (0);
	}
	ft_get2(line, &tmp);
	return (1);
}
