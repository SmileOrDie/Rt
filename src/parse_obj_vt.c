/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_vt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:47:49 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/14 16:50:21 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
                e->f_obj[1][i]->tab.vtx = ft_check_pow(line, s, y);
                //printf("ft_parse_obj_vt :f_obj[0][%d]->x == %f || S = [%d]\n", i, e->f_obj[1][i]->x, s);
                s += y + 1;
                y = ft_len_nb(line, s);
                e->f_obj[1][i]->tab.vty = ft_check_pow(line, s, y);
                 //printf("ft_parse_obj_vt :f_obj[1][%d]->y == %f || S = [%d]\n", i, e->f_obj[1][i]->y, s);
                 //printf("ft_parse_obj_vt :f_obj[1][%d]->z == %f || S = [%d]\n", i, e->f_obj[1][i]->z, s);
                s += y + 2;
        }
        else
            ft_error(OBJ_F, "remp_tab_vt");
        i++;
    }
}

int         ft_parse_obj_vt(char *line, t_env *e, int i)
{
    int     taille_vt;
    int     x;
    int     s;

    x = 0;
    taille_vt = 0;
    s = i;
    if (line[i] == 'v')
    {
        while (line[i + 1] != 'n' && line[i] != 'f')
        {
            if (line[i] == 'v')
                taille_vt++;
            i++;
        }
        taille_vt -= 1;
        //printf("ft_parse_obj_vt : taille_vt == %d\n", taille_vt);
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
        ft_error(OBJ_F, "ft_parse_obj_vt");
    return (i);
}
