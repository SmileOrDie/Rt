/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_obj_json.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 13:32:28 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/27 18:13:22 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int		save_obj(t_env *e, t_parse_obj *obj, int fd)
{
	if (obj != NULL)
	{
		while (obj)
		{
			printf("\nobj->next == %d \n", obj->obj.type);
			if (obj->obj.type == 6)
				copy_square(obj->obj, fd, e);
			else if (obj->obj.type == 7)
				copy_cube(obj->obj, fd, e);
			else if (obj->obj.type == 1)
				copy_sphere(obj->obj, fd, e);
			else if (obj->obj.type == 2)
				copy_plan(obj->obj, fd, e);
			else if (obj->obj.type == 3)
				copy_cylindre(obj->obj, fd, e);
			else if (obj->obj.type == 4)
				copy_cone(obj->obj, fd, e);
			else if (obj->obj.type == 5)
				copy_circle(obj->obj, fd, e);
			obj = obj->next;
		}
		return (1);
	}
	return (-1);
}

void			save_scene(t_env *e, char *id, int fd)
{
	static int		i = 0;
	t_parse_obj		*obj;
	t_parse_light	*light;
	char			name[256];

	light = e->parse_light;
	fd = -1;
	obj = NULL;
	obj = e->parse_obj;
	id = ft_itoa(i);
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
	i++;
}
