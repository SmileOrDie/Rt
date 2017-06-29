/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_keypress3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:48:14 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 14:49:01 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			add_new_texture2(t_envg *e, char **new, int y)
{
	new[y] = ft_strdup(e->line[41]);
	new[y + 1] = NULL;
	free(e->e->path_tex);
	e->e->path_tex = new;
	e->e->nb_tex++;
}

void			add_new_texture(t_envg *e)
{
	char	**new;
	int		y;

	y = 0;
	clean_str(&e->line[41], 0);
	while ((e->e->path_tex)[y] != NULL)
	{
		if (ft_strcmp(e->line[41], (e->e->path_tex)[y]) == 0)
			break ;
		y++;
	}
	if ((e->e->path_tex)[y] == NULL)
	{
		if (!(new = (char **)malloc(sizeof(char *) * (y + 1))))
			ft_error(MALLOC, "add_new_texture => interface_keypress.c");
		y = 0;
		while ((e->e->path_tex)[y] != NULL)
		{
			new[y] = (e->e->path_tex)[y];
			y++;
		}
		add_new_texture2(e, new, y);
	}
	free(e->e->texture);
	e->error = add_texture(e);
}
