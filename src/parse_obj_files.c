/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:40:22 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/14 16:21:34 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double         ft_check_pow(char *str, int s, int y)
{
    int i;

    i = s;
    //printf("check_pow : i == [%d] ||| y == [%d]\n", i, y);
    while (str[i] && i <= (y + s))
    {
        if (str[i] != 'e')
            i++;
        else if (str[i] == 'e')
            return(0);
    }
//    printf("check_pow : s == [%d] ||| y == [%d]\n", s, y + s);
    return (ft_for_atof(str, s, y + (s)));
}

int          ft_len_nb(char *line, int s)
{
    int y;

    y = 0;
    while (line[s] != ' ' && line[s] != '\n' && line[s] != '\\')
    {
        y++;
        s++;
    }
    if (line[s] == '\n')
        y--;
//    printf("-- y == %d\n", y );
    return (y);
}


void			ft_parse_obj_files1(char *name, t_env *e)
{
	int			fd;
	struct stat	st;
	char		*line;
    int         i;

    i = 0;
    printf("debut parse_obj_f\n");
	if (stat(name, &st) != 0)
		ft_error("File doesn't exist", "ft_parse_obj_files1");
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error("Can't open file", "ft_parse_obj_files1");
	line = malloc(st.st_size + 1);
	line[st.st_size] = '\0';
	read(fd, line, st.st_size);
    e->f_obj = (t_parse_obj_f ***)malloc(sizeof(t_parse_obj_f **) * (4));

    printf("PARSE V\n");
    i = ft_parse_obj_v(line, e);
    if (line[i + 1] == 't')
    {
        printf("PARSE Vt\n");
        i = ft_parse_obj_vt(line, e, i);
    }
    if (line[i + 1] == 'n')
    {
        printf("PARSE VN\n");
        i = ft_parse_obj_vn(line, e, i);
    }
   if (line[i + 1] == 'f')
   {
       i++;
       printf("PARSE F\n");
       i = ft_parse_obj_f(line, e, i);
    }
    printf("FIN : line[i] == [%c]\n", line[i + 1]);
    close(fd);
	free(line);
}
