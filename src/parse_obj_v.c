/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:45:49 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/14 16:03:23 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void         remp_tab_v(t_env *e, char *line, int s, int size_v)
{
    int     i;
    int     y;

    y = 0;
    i = 0;
    while (i <= size_v)
    {
        if (line[s] == 'v')
        {
            s += 2;
            y = ft_len_nb(line, s);
            //p rintf("remp tab : i=%d\n", i);
            e->f_obj[0][i]->tab.vx = ft_check_pow(line, s, y);
            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[0][i]->tab.vy = ft_check_pow(line, s, y);
            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[0][i]->tab.vz = ft_check_pow(line, s, y);
            s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_v");
        i++;
    }
}

int        ft_parse_obj_v(char *line, t_env *e)
{
    int     i;
    int     taille_v;
    int     s;

    taille_v = 0;
    i = 0;
    s = 0;
    while ((line[i]) && (line[i] != 'v' || line[i + 1] != ' '))
        i++;
    s = i;
    if (line[i] == 'v')
    {
        while (line[i + 1] != 't' && line[i + 1] != 'f' && line[i + 1] != 'n')
        {
                //printf("ft_parse_obj_v : i == %d\n", i);
            if (line[i] == 'v')
                taille_v++;
            i++;
        }
        taille_v -= 1;
        printf("ft_parse_obj_v : taille_v == %d\n", taille_v);
        e->f_obj[0] = (t_parse_obj_f **)malloc(sizeof(t_parse_obj_f *) * (taille_v + 1));
        int x = 0;
        while (x <= taille_v)
        {
            e->f_obj[0][x] = (t_parse_obj_f *)malloc(sizeof(t_parse_obj_f));
            x++;
        }
        e->f_obj[0][0]->start = s;
        e->f_obj[taille_v] = NULL;
        remp_tab_v(e, line, e->f_obj[0][0]->start, taille_v);
    }
    else
        ft_error(OBJ_F, "ft_parse_obj_v");
    // //printf("ft_parse_obj_files2 :f_obj[0][0]->x == %f\n", e->f_obj[0][0]->x);
    //printf("i de position = %d\n", i);
    //printf("line[i] = %c\n", line[i]);
    return (i);
}
