/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:40:22 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/13 20:19:46 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static double         ft_check_pow(char *str, int s, int y)
{
    int i;

    i = s;
    printf("check_pow : i == [%d] ||| y == [%d]\n", i, y);
    while (str[i] && i <= (y + s))
    {
        if (str[i] != 'e')
            i++;
        else if (str[i] == 'e')
            return(0);
    }
    printf("check_pow : s == [%d] ||| y == [%d]\n", s, y + s);
    return (ft_for_atof(str, s, y + (s)));
}

static int          ft_len_nb(char *line, int s)
{
    int y;

    y = 0;
    while (line[s] != ' ' && line[s] != '\n')
    {
        y++;
        s++;
    }
    if (line[s] == '\n')
        y--;
    printf("-- y == %d\n", y );
    return (y);
}

static void         remp_tab_v(t_env *e, char *line, int s, int size_v)
{
    int     i;
    int     y;

    y = 0;
    i = 0;
    while (i <= size_v)
    {
        // printf("remp tab : i < size_v = [%d < %d]\n", i, size_v);
        if (line[s] == 'v')
        {
            s += 2;
            y = ft_len_nb(line, s);
            //p rintf("remp tab : i=%d\n", i);
            e->f_obj[0][i]->x = ft_check_pow(line, s, y);
            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[0][i]->y = ft_check_pow(line, s, y);
            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[0][i]->z = ft_check_pow(line, s, y);
            // printf("ft_parse_obj_files1 :f_obj[0][%d]->x == %f || S = [%d]\n", i, e->f_obj[0][i]->x, s);
            // printf("ft_parse_obj_files1 :f_obj[0][%d]->y == %f || S = [%d]\n", i, e->f_obj[0][i]->y, s);
            // printf("ft_parse_obj_files1 :f_obj[0][%d]->z == %f || S = [%d]\n", i, e->f_obj[0][i]->z, s);
            s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_v");
        i++;
    }
}

static int        ft_parse_obj_files2(char *line, t_env *e)
{
    int     i;
    int     taille_v;
    int     s;

    s = 0;
    taille_v = 0;
    i = 0;
    while ((line[i]) && (line[i] != 'v' || line[i + 1] != ' '))
        i++;
    s = i;
    printf("ft_parse_obj_files2 : i == %d\n", i);
    if (line[i] == 'v')
    {
        while (line[i + 1] != 't')
        {
            if (line[i] == 'v')
                taille_v++;
            i++;
        }
        taille_v -= 1;
        printf("ft_parse_obj_files2 : taille_v == %d\n", taille_v);
        e->f_obj[0] = (t_parse_obj_f **)malloc(sizeof(t_parse_obj_f *) * (taille_v + 1));
        int x = 0;
        while (x <= taille_v)
        {
             e->f_obj[0][x] = (t_parse_obj_f *)malloc(sizeof(t_parse_obj_f));
            x++;
        }
        e->f_obj[taille_v] = NULL;
        remp_tab_v(e, line, s, taille_v);
    }
    else
        ft_error(OBJ_F, "ft_parse_obj_files2");
    // printf("ft_parse_obj_files2 :f_obj[0][0]->x == %f\n", e->f_obj[0][0]->x);
    printf("i de position = %d\n", i);
    printf("line[i] = %c\n", line[i]);
    return (i);
}

static void         remp_tab_vt(t_env *e, char *line, int s, int size_vt)
{
    int     i;
    int     y;

    y = 0;
    i = 0;
    while (i <= size_vt)
    {
        if (line[s] == 'v' && line[s + 1] == 't')
        {
                s += 3;
                y = ft_len_nb(line, s);
                e->f_obj[1][i]->x = ft_check_pow(line, s, y);
                printf("ft_parse_obj_files3 :f_obj[0][%d]->x == %f || S = [%d]\n", i, e->f_obj[1][i]->x, s);
                s += y + 1;
                y = ft_len_nb(line, s);
                e->f_obj[1][i]->y = ft_check_pow(line, s, y);
                 printf("ft_parse_obj_files3 :f_obj[1][%d]->y == %f || S = [%d]\n", i, e->f_obj[1][i]->y, s);
                y = ft_len_nb(line, s);
                e->f_obj[1][i]->z = 0;
                 printf("ft_parse_obj_files3 :f_obj[1][%d]->z == %f || S = [%d]\n", i, e->f_obj[1][i]->z, s);
                s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_vt");
        i++;
    }
}

static int         ft_parse_obj_files3(char *line, t_env *e, int i)
{
    int     taille_vt;
    int     x;
    int     s;

    x = 0;
    taille_vt = 0;
    s = i;
    if (line[i] == 'v')
    {
        while (line[i + 1] != 'n')
        {
            if (line[i] == 'v')
                taille_vt++;
            i++;
        }
        taille_vt -= 1;
        printf("ft_parse_obj_files3 : taille_vt == %d\n", taille_vt);
        e->f_obj[1] = (t_parse_obj_f **)malloc(sizeof(t_parse_obj_f *) * (taille_vt + 1));
        while (x <= taille_vt)
        {
            e->f_obj[1][x] = (t_parse_obj_f *)malloc(sizeof(t_parse_obj_f));
            x++;
        }
        e->f_obj[taille_vt] = NULL;
        remp_tab_vt(e, line, s, taille_vt);
    }
    else
        ft_error(OBJ_F, "ft_parse_obj_files3");
    return (i);
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
    i = ft_parse_obj_files2(line, e);
    i = ft_parse_obj_files3(line, e, i);
    close(fd);
	free(line);
}
