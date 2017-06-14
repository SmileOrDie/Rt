/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 15:00:20 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/14 16:24:03 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static char         *for_atoi(char *line, int s, int y)
{
    int tmp;
    char *str;

    tmp = 0;
    printf("y = %d, s = %d\n", y, s);
    str = (char*)malloc(sizeof(char) * (s - y) + 1);
    while (tmp < (y - s))
    {
        str[tmp] = line[s];
        tmp++;
        s++;
    }
    return (str);
}

static void         remp_tab_f(t_env *e, char *line, int s, int size_f)
{
    int     i;
    int     y;
    int     pos;
//e->tab[0][0]->start;

    pos = 0;
    y = 0;
    i = 0;
    while (i <= size_f)
    {
        if (line[s] == 'f')
        {
            s += 2;
            y = ft_len_nb(line, s);
            pos = ft_atoi(for_atoi(line, s, y));

            e->f_obj[3][i]->tab.vx = e->f_obj[0][pos + e->f_obj[0][0]->start]->tab.vx;

            s += y;
            y = ft_len_nb(line, s);
            pos = ft_atoi(for_atoi(line, s, y));

            e->f_obj[3][i]->tab.vy = e->f_obj[0][pos + e->f_obj[0][0]->start]->tab.vy;

            s += y;
            y = ft_len_nb(line, s);
            pos = ft_atoi(for_atoi(line, s, y));

            e->f_obj[3][i]->tab.vz = e->f_obj[0][pos + e->f_obj[0][0]->start]->tab.vz;

            s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_f");
        i++;
    }
}

int        ft_parse_obj_f(char *line, t_env *e, int i)
{
    int     taille_f;
    int     s;
    int     x;

    x = 0;
    taille_f = 0;
    s = i;
    printf("----------- line == [%c]\n", line[i]);
    if (line[i] == 'f')
    {
        while (line[i + 1] && line[i + 1] != 't' && line[i + 1] != 'n')
        {
                //printf("ft_parse_obj_f : i == %d\n", i);
            if (line[i] == 'f')
                taille_f++;
            i++;
        }
        taille_f -= 1;
        printf("ft_parse_obj_files2 : taille_f == %d\n", taille_f);
        if (!(e->f_obj[3] = (t_parse_obj_f **)malloc(sizeof(t_parse_obj_f *) * (taille_f + 1))))
                ft_error("f_obj faille maolloc", "parse obj_f");
        while (x <= taille_f)
        {  // printf("%d\n", x);
            if (!(e->f_obj[3][x] = (t_parse_obj_f *)malloc(sizeof(t_parse_obj_f))))
                ft_error("f_obj faille maolloc", "parse obj_f");
            x++;
        }
        printf("fuck one\n");
        e->f_obj[taille_f] = NULL;
        remp_tab_f(e, line, s, taille_f);
    }
    else
        ft_error(OBJ_F, "ft_parse_obj_f");
    // //printf("ft_parse_obj_files2 :f_obj[3][3]->x == %f\n", e->f_obj[3][3]->x);
    //printf("i de position = %d\n", i);
    //printf("line[i] = %c\n", line[i]);
    return (i);
}
