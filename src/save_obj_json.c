/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_obj_json.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 13:32:28 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/24 11:53:01 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static int		save_obj(t_envg *e, t_parse_obj *obj, int fd)
{
	if (obj != NULL)
	{
		while (obj)
		{
			if (obj->obj.type == 6)
				copy_square(obj->obj, fd, e);
			else if (obj->obj.type == 7)
				copy_cube(obj->obj, fd, e);
			else if (obj->obj.type == 1)
				copy_sphere(obj->obj, fd, e);
			else if (obj->obj.type == 2)
				copy_plan(obj->obj, fd, e);
			else if (obj->obj.type == 3 || obj->obj.type == 9)
				copy_cylindre(obj->obj, fd, e);
			else if (obj->obj.type == 4 || obj->obj.type == 8)
				copy_cone(obj->obj, fd, e);
			else if (obj->obj.type == 5)
				copy_circle(obj->obj, fd, e);
			obj = obj->next;
		}
		return (1);
	}
	return (-1);
}

static void		create_path(char **id)
{
	static int		i = 0;
	char			name[256];

	if (i == 256)
		ft_error("Too much existing backup", "save_obj_json");
	*id = ft_itoa(i);
	ft_strcpy(name, "./scenes_file/scene_file_");
	ft_strcat(name, *id);
	ft_strcat(name, ".json");
	i++;
	while (!access(name, W_OK))
	{
		if (i == 256)
			ft_error("Too much existing backup", "save_obj_json");
		*id = ft_itoa(i);
		ft_strcpy(name, "./scenes_file/scene_file_");
		ft_strcat(name, *id);
		ft_strcat(name, ".json");
		i++;
	}
}

void			save_scene(t_envg *e, char *id, int fd)
{
	t_parse_obj		*obj;
	t_parse_light	*light;
	char			name[256];

	light = e->parse_light;
	fd = -1;
	obj = NULL;
	obj = e->parse_obj;
	create_path(&id);
	ft_strcpy(name, "./scenes_file/scene_file_");
	ft_strcpy(name, "./scenes_file/scene_file_");
	ft_strcat(name, id);
	ft_strcat(name, ".json");
	if ((fd = open(name, O_CREAT | O_WRONLY, 0644)) <= 0)
		ft_error("fichier deja existant", " save_scene");
	ft_putstr_fd(fd, "{\n\t\"anti-aliasing\" : ", ft_itoa(e->anti_a), NULL);
	ft_putstr_fd(fd, ",\n\t\"ambient\" : ", ft_dtoa(e->amb), ",\n", NULL);
	save_obj(e, obj, fd);
	save_light_and_cam(e, fd, light);
	ft_putstr_fd(fd, "}", NULL);
	close(fd);
	free(id);
}
