/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 16:18:11 by phmoulin          #+#    #+#             */
/*   Updated: 2017/11/09 13:38:57 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		clean_str(char **clean, int f)
{
	int		i;

	i = ft_strlen(*clean) - 1;
	if (f == 0)
	{
		while ((*clean)[i] == ' ' || (*clean)[i] == '\n' || (*clean)[i] == '\t')
			i--;
		(*clean)[i + 1] = '\0';
		return ;
	}
	else if (*clean && i >= 0)
	{
		while (i > 0)
			(*clean)[i--] = '\0';
		(*clean)[i] = '\0';
	}
}

static void	clean_env(t_envg *e)
{
	e->parse_obj = NULL;
	e->parse_light = NULL;
	clean_str(&e->line[42], 0);
	ft_parse_j(e->line[42], e);
	init_id(e);
	clean_str(&e->line[42], 1);
	modif_default(e);
	home_tab(e);
}

void		free_env_parse(t_envg *e)
{
	t_parse_light	*tmp;
	t_parse_obj		*tmp2;

	e->anti_a = 1;
	e->cam.set = 0;
	while (e->parse_obj)
	{
		free(e->parse_obj->obj.name);
		tmp2 = e->parse_obj->next;
		free(e->parse_obj);
		e->parse_obj = tmp2;
	}
	while (e->parse_light)
	{
		free(e->parse_light->light.name);
		tmp = e->parse_light->next;
		free(e->parse_light);
		e->parse_light = tmp;
	}
	clean_env(e);
}

static int	check_path_tex(t_envg *e, int *y)
{
	struct stat	test;
	int			len;

	*y = -1;
	while (e->path_tex != NULL && (e->path_tex)[++(*y)] != NULL)
	{
		if (ft_strcmp(e->line[41], (e->path_tex)[*y]) == 0)
			return (-9);
	}
	len = ft_strlen(e->line[41]) - 4;
	if ((ft_strcmp(((e->line[41]) + len), ".xpm")) && (
		ft_strcmp(((e->line[41]) + len), ".XPM")) && (
	ft_strcmp(((e->line[41]) + len), ".jpg")) && (
	ft_strcmp(((e->line[41]) + len), ".png")) && (
	ft_strcmp(((e->line[41]) + len), ".jpeg")) && (
	ft_strcmp(((e->line[41]) + len), ".JPG")) && (
	ft_strcmp(((e->line[41]) + len), ".PNG")) && (
	ft_strcmp(((e->line[41]) + len), ".JPEG")) && (
	ft_strcmp(((e->line[41]) + len), ".gif")) && (
	ft_strcmp(((e->line[41]) + len), ".GIF")))
		return (-8);
	else if (stat(e->line[41], &test) == -1)
		return (-7);
	return (1);
}

void		add_new_texture(t_envg *e)
{
	char	**new;
	int		y;

	clean_str(&e->line[41], 0);
	e->error = check_path_tex(e, &y);
	if (e->error > 0 && (e->path_tex == NULL || e->path_tex[y] == NULL))
	{
		if (!(new = (char **)malloc(sizeof(char *) * (y + 2))))
			ft_error(MALLOC, "add_new_texture => interface_keypress.c");
		y = 0;
		while (e->path_tex != NULL && (e->path_tex)[y] != NULL)
		{
			new[y] = (e->path_tex)[y];
			y++;
		}
		new[y] = ft_strdup(e->line[41]);
		new[y + 1] = NULL;
		free(e->path_tex);
		e->path_tex = new;
		e->nb_tex++;
	}
	e->error *= -1;
	clean_str(&e->line[41], 1);
	home_tab(e);
}
