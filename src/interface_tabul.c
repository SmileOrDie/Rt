/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_tabul.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:01:16 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/16 19:28:00 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

char		*tabulation(t_tabu *t, int id)
{
	char			*ret;
	struct stat		sb;
	struct dirent	*dp;
	char			path[300];

	ret = NULL;
	t->dirp = opendir(t->name_path);
	if (t->dirp == NULL)
		return (NULL);
	t->index = 0;
	while ((dp = readdir(t->dirp)) != NULL)
	{
		ft_strcpy(path, t->name_path);
		ft_strcat(path, dp->d_name);
		if (stat(path, &sb) == -1)
			return (NULL);
		if (dp->d_name[0] != '.' && !((sb.st_mode & S_IFMT) == S_IFDIR))
		{
			if (t->index == id)
				ret = ft_strdup(path);
			t->index++;
		}
	}
	closedir(t->dirp);
	return (ret);
}

void		switch_tabul(t_envg *e)
{
	static int	i_tex = 0;
	static int	i_scene = 0;
	char		*string;

	e->tab_texture.name_path = "texture_file/";
	e->tab_scene.name_path = "scenes_file/";
	if (e->pos == 41)
	{
		string = tabulation(&(e->tab_texture), i_tex);
		string != NULL ? ft_strcpy(e->line[e->pos], string) : 0;
		i_tex = (i_tex < e->tab_texture.index - 1) ? i_tex + 1 : 0;
		free(string);
	}
	else if (e->pos == 42)
	{
		string = tabulation(&(e->tab_scene), i_scene);
		ft_strcpy(e->line[e->pos], string);
		i_scene = (i_scene < e->tab_scene.index - 1) ? i_scene + 1 : 0;
		free(string);
	}
}
