/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:01:43 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 19:34:11 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			free_env_parse(t_envg *e)
{
// <<<<<<< HEAD
	free(e->e->cam);
	e->e->cam = NULL;
	while (e->e->parse_obj)
	{
		free(e->e->parse_obj);
		e->e->parse_obj = e->e->parse_obj->next;
	}
	while (e->e->parse_light)
	{
		free(e->e->parse_light);
		e->e->parse_light = e->e->parse_light->next;
	}
	e->e->parse_obj = NULL;
	e->e->parse_light = NULL;
	clean_str(&e->line[42], 0);
	ft_parse_j(e->line[42], e->e);
	init_id(e->e);
	clean_str(&e->line[42], 1);
	modif_default(e);
	home_tab(e);
// =======
//     int i;
//
//     i = ft_strlen(*clean) - 1;
//     if (f == 0)
//     {
//         while ((*clean)[i] == ' ' || (*clean)[i] == '\n' || (*clean)[i] == '\t')
//             i--;
//         (*clean)[i + 1] = '\0';
//         return ;
//     }
//     else if (*clean && i >= 0)
//     {
//         while (i > 0)
//             (*clean)[i--] = '\0';
//         (*clean)[i] = '\0';
//     }
// >>>>>>> master
}

static int		interface_keypress_1(t_envg *e)
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
	else if (e->volet.info == 1 && e->pos == 41 && e->line[e->pos][0] != '\0')
		add_new_texture(e);
	else if (e->volet.info == 1 && e->pos == 42 && e->line[e->pos][0] != '\0')
		free_env_parse(e);
	return (1);
}

// <<<<<<< HEAD
static int		interface_keypress_2(int key, t_envg *e, int *val, char *li)
{
	char *pr;
	int  pression;

	pression = 0;
	e->volet.info == 1 ? info_tab(e) : 0;
	pr = ft_print_key(key, e);
	if (!(ft_strcmp(pr, "right delete")) || !(ft_strcmp(pr, "delete")))
	{
		*val = ((e->pos < 40 && e->pos > 42) || (e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26)) ? 3 : 30;
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
// =======
// void    convert_file(char **path)
// {
//     char *new_path;
//     int len;
//     char line[512];

//     len = ft_strlen(*path);
//     new_path = ft_strdup(*path);
//     new_path[len - 1] = 'm';
//     new_path[len - 2] = 'p';
//     new_path[len - 3] = 'x';
//     ft_strcpy(line, "convert ");
//     ft_strcat(line, *path);
//     ft_strcat(line, " ");
//     ft_strcat(line, new_path);
//     system(line);
//     printf("line = %s\n", line);
//     free(*path);
//     path = &new_path;
// }
//
// int     add_texture(t_envg *e)
// {
//     int         x;
//     char        *path;
//     struct stat test;
//
//     x = 0;
//     while (e->e->path_tex[x])
//         x++;
//     e->e->nb_tex = x;
//     if (!(e->e->texture = (t_mlx *)malloc(sizeof(t_mlx) * x)))
//          e->error = 6;
//     x = 0;
//     while (e->e->path_tex[x])
//     {
//         path = ft_strjoin("./", e->e->path_tex[x]);
//         // if (!ft_strcmp(path + (ft_strlen(path) - 4), ".png"))
//         //     convert_file(&path);
//         if (stat(path, &test) == -1)
//             return (failed_texture(e, 7, x));
//         if (!(e->e->texture[x].img = mlx_xpm_file_to_image(e->e->mlx->mlx, path, &e->e->texture[x].w, &e->e->texture[x].h)))
//             return (failed_texture(e, 8, x));
//         if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img,
//             &e->e->texture[x].bpp, &e->e->texture[x].sizeline, &e->e->texture[x].endian)))
//             return (failed_texture(e, 9, x));
//         x++;
//     }
//     return (-1);
// >>>>>>> master
}

static int		exeption_key(int key)
{
// <<<<<<< HEAD
	if ((key >= 123 && key <= 126) || key == 81 || key == 75 || key == ESC)
		return (1);
	if (key == 260 || key == 262 || key == 269 || key == 279 || key == 115)
		return (1);
	if (key == 116 || key == 117 || key == 119 || key == 121 || key == 71)
		return (1);
	return (0);
}
// =======
//     char    **new;
//     int     y;
//
//     y = 0;
//     clean_str(&e->line[41], 0);
//     while ((e->e->path_tex)[y] != NULL)
//     {
//         if (ft_strcmp(e->line[41], (e->e->path_tex)[y]) == 0)
//             break ;
//         y++;
//     }
//     if ((e->e->path_tex)[y] == NULL)
//     {
//         if (!(new = (char **)malloc(sizeof(char *) * (y + 1))))
//             ft_error(MALLOC, "add_new_texture => interface_keypress.c");
//         y = 0;
//         while ((e->e->path_tex)[y] != NULL)
//         {
//             new[y] = (e->e->path_tex)[y];
//             y++;
//         }
//         new[y] = ft_strdup(e->line[41]);
//         new[y + 1] = NULL;
//         free(e->e->path_tex);
//         e->e->path_tex = new;
//         e->e->nb_tex++;
//     }
//     free(e->e->texture);
//     e->error = add_texture(e);
//     clean_str(&e->line[41], 1);
//     home_tab(e);
// >>>>>>> master
// }

int				interface_keypress(int key, t_envg *e)
{
<<<<<<< HEAD
	char	*line;
	int		val;
	int		pression;

	line = e->line[e->pos];
	val = 0;
	if (e->f_key && exeption_key(key))
		return (1);
	else if (e->f_key)
	{
		(key == 48 && e->volet.info == 1) ? switch_tabul(e) : 0;
		pression = interface_keypress_2(key, e, &val, line);
		e->volet.info == 1 ? e->pos -= 40 : 0;
		pression == 0 ? load_img(e, e->pos_value[e->pos] + 1) : 0;
		e->volet.info == 1 ? e->pos += 40 : 0;
		print_line(e, e->pos, val);
	}
	return (1);
// =======
//     free(e->e->cam);
//     e->e->cam = NULL;
//     while (e->e->parse_obj)
//     {
//         free(e->e->parse_obj);
//         e->e->parse_obj = e->e->parse_obj->next;
//     }
//     while (e->e->parse_light)
//     {
//         free(e->e->parse_light);
//         e->e->parse_light = e->e->parse_light->next;
//     }
//     e->e->parse_obj = NULL;
//     e->e->parse_light = NULL;
//     clean_str(&e->line[42], 0);
//     ft_parse_j(e->line[42], e->e);
//     init_id(e->e);
//     clean_str(&e->line[42], 1);
//     modif_default(e);
//     home_tab(e);
}
//
// static int     interface_keypress_1(t_envg *e)
// {
//     if (e->volet.add == 1)
//     {
//         creat_elem(e);
//         e->i_lst = 0;
//         e->page = 0;
//         home_tab(e);
//     }
//     else if (e->volet.conf == 1 && e->mod == 1)
//     {
//         creat_elem(e);
//         (e->light == -1) ? del_elem(e, e->obj + e->page) :
//         del_elem(e, e->light + e->page);
//         e->i_lst = 0;
//         e->page = 0;
//         home_tab(e);
//     }
//     else if (e->volet.info == 1 && e->pos == 41 && e->line[e->pos][0] != '\0')
//         add_new_texture(e);
//     else if (e->volet.info == 1 && e->pos == 42 && e->line[e->pos][0] != '\0')
//         free_env_parse(e);
//     return (1);
// }

// static int     interface_keypress_2(int key, t_envg *e, int *val, char *li)
// {
//     char *pr;
//     int  pression;
//
//     pression = 0;
//     e->volet.info == 1 ? info_tab(e) : 0;
//     pr = ft_print_key(key, e);
//     if (!(ft_strcmp(pr, "right delete")) || !(ft_strcmp(pr, "delete")))
//     {
//         *val = ((e->pos < 40 && e->pos > 42) || (e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26))
//         ? 3 : 30;
//         del_line(e);
//     }
//     else if (!(ft_strcmp(pr, "return")) || !(ft_strcmp(pr, "enter")))
//         pression = interface_keypress_1(e);
//     else if (((e->pos > 2 && e->pos <= 15) || e->pos == 31 || (e->pos >= 19 && e->pos <= 26)))
//     {
//         *val = 3;
//         add_line(li, pr, 1);
//     }
//     else if (e->pos == 2 || (e->pos > 40 && e->pos <= 42))
//     {
//         *val = 30;
//         add_line(li, pr, 0);
//     }
//     return (pression);
// }
//
// static int      exeption_key(int key)
// {
//     if ((key >= 123 && key <= 126) || key == 81 || key == 75 || key == ESC)
//         return (1);
//     if (key == 260 || key == 262 || key == 269 || key == 279 || key == 115)
//         return (1);
//     if (key == 116 || key == 117 || key == 119 || key == 121 || key == 71)
//         return (1);
//     return (0);
// }

// int             interface_keypress(int key, t_envg *e)
// {
//     char *line;
//     int  val;
//     int pression;
//
//     line = e->line[e->pos];
//     val = 0;
//     if (e->f_key && exeption_key(key))
//         return (1);
//     else if (e->f_key)
//     {
//         (key == 48 && e->volet.info == 1) ? switch_tabul(e) : 0;
//         pression = interface_keypress_2(key, e, &val, line);
//         e->volet.info == 1 ? e->pos -= 40 : 0;
//         pression == 0 ? load_img(e, e->pos_value[e->pos] + 1) : 0;
//         e->volet.info == 1 ? e->pos += 40 : 0;
//         print_line(e, e->pos, val);
//     }
//     return (1);
// >>>>>>> master
// }
