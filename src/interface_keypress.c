/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:05:51 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/28 15:35:58 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void    add_new_texture(t_envg *e)
{
    char    *path;
    char    **new;
    int     y;

    y = 0;
    while ((e->e->path_tex)[y] != NULL)
    {
        if (ft_strcmp(e->line[41], (e->e->path_tex)[y]) == 0)
            break ;
        y++;
    }
    if ((e->path_tex)[y] == NULL)
    {
        if (new = (char **)malloc(sizeof(char *) * (y + 2)))
            ft_error(MALLOC, "add_new_texture => interface_keypress.c");
        y = 0;
        while ((e->path_tex)[y] != NULL)
        {
            new[y] = (e->path_tex)[y];
            y++;
        }
        new[y] = ft_strdup(e->line[41]);
        new[y + 1] = NULL;
        free(e->path_tex);
        e->path_tex = new;
        e->e->nb_tex++;
    }
}

static int     interface_keypress_1(t_envg *e)
{
    if (e->volet.add == 1)
    {
        creat_elem(e);
        e->i_lst = 0;
        e->page = 0;
        home_tab(e);
    }
    else if (e->volet.conf == 1 && e->mod == 1)
    {
        creat_elem(e);
        (e->light == -1) ? del_elem(e, e->obj + e->page) :
        del_elem(e, e->light + e->page);
        e->i_lst = 0;
        e->page = 0;
        home_tab(e);
    }
    else if (e->volet.info == 1 && e->line[41][0] != "\0")
        add_new_texture(e);
    return (1);
}

static int     interface_keypress_2(int key, t_envg *e, int *val, char *li)
{
    char *pr;
    int  pression;

    pression = 0;
    pr = ft_print_key(key, e);
    if (!(ft_strcmp(pr, "right delete")) || !(ft_strcmp(pr, "delete")))
    {
        *val = ((e->pos < 40 && e->pos > 42) || (e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26))
        ? 3 : 30;
        del_line(e);
    }
    else if (!(ft_strcmp(pr, "return")) || !(ft_strcmp(pr, "enter")))
        pression = interface_keypress_1(e);
    else if (((e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26)))
    {
        *val = 3;
        add_line(li, pr, 1);
    }
    else if (e->pos == 2 || (e->pos > 40 && e->pos <= 42))
    {
        *val = 30;
        add_line(li, pr, 0);
    }
    return (pression);
}

static int      exeption_key(int key)
{
    if ((key >=123 && key <= 126) || key == 81 || key == 75)
        return (1);
    if (key == 260 || key == 262 || key == 269 || key == 279 || key == 115)
        return (1);
    if (key == 116 || key == 117 || key == 119 || key == 121 || key == 71)
        return (1);
    return (0);
} 

int             interface_keypress(int key, t_envg *e)
{
    char *line;
    int  val;
    int pression;

    line = e->line[e->pos];
    val = 0;
    if (exeption_key(key))
        return (1);
    else if (e->f_key)
    {
        pression = interface_keypress_2(key, e, &val, line);
        // (((e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26)) &&
        //     pression == 0) ? load_img(e, e->pos_value[e->pos] + 1) : 0;
        // printf("%d\n", e->pos);
        e->volet.info == 1 ? e->pos -= 40 : 0;
        pression == 0 ? load_img(e, e->pos_value[e->pos] + 1) : 0;
        e->volet.info == 1 ? e->pos += 40 : 0;
        print_line(e, e->pos, val);
    }
    return (1);
}
