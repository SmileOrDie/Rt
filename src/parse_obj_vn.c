/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_vn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:52:48 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/14 15:27:52 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void         remp_tab_vn(t_env *e, char *line, int s, int size_vn)
{
    int     i;
    int     y;

    y = 0;
    i = 0;
        while (i <= size_vn)
    {
        if (line[s] == 'v')
        {
            s += 3;
            y = ft_len_nb(line, s);
            //p rintf("remp tab : i=%d\n", i);
            e->f_obj[2][i]->tab.vnx = ft_check_pow(line, s, y);
            ////printf("ft_parse_obj_vn : f_obj[2][%d]->x == %f || S = [%d]\n", i, e->f_obj[2][i]->x, s);

            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[2][i]->tab.vny = ft_check_pow(line, s, y);
            ////printf("ft_parse_obj_vn :f_obj[2][%d]->y == %f || S = [%d]\n", i, e->f_obj[2][i]->y, s);

            s += y + 1;
            y = ft_len_nb(line, s);
            e->f_obj[2][i]->tab.vnz = ft_check_pow(line, s, y);
            ////printf("ft_parse_obj_vn :f_obj[2][%d]->z == %f || S = [%d]\n", i, e->f_obj[2][i]->z, s);

            s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_vn");
        i++;
    }
}

int        ft_parse_obj_vn(char *line, t_env *e, int i)
{
    int     taille_vn;
    int     s;
    int     x;

    x = 0;
    taille_vn = 0;

    s = i;
    //printf("ft_parse_obj_vn : i == %d\n", i);
    if (line[i] == 'v')
    {
        while (line[i + 1] != 't' && line[i + 1] != 'f')
        {
            if (line[i] == 'v')
                taille_vn++;
            i++;
        }
        taille_vn -= 1;
        //printf("ft_parse_obj_vn : taille_vn == %d\n", taille_vn);
        e->f_obj[2] = (t_parse_obj_f **)malloc(sizeof(t_parse_obj_f *) * (taille_vn + 1));
        while (x <= taille_vn)
        {
             e->f_obj[2][x] = (t_parse_obj_f *)malloc(sizeof(t_parse_obj_f));
            x++;
        }
        e->f_obj[taille_vn] = NULL;
        remp_tab_vn(e, line, s, taille_vn);
    }
    else
        ft_error(OBJ_F, "ft_parse_obj_vn");
    // //printf("ft_parse_obj_vn :f_obj[2][2]->x == %f\n", e->f_obj[2][2]->x);
    //printf("i de position = %d\n", i);
    //printf("line[i] = %c\n", line[i]);
    return (i);
}
