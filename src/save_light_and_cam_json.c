/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_light_and_cam_json.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:39:12 by phmoulin          #+#    #+#             */
/*   Updated: 2017/07/27 18:13:34 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void		save_light(t_parse_light *light, int fd)
{
	ft_putstr_fd(fd, "\t\"light\" :\n\t{\n\t\t\"name\": \"", light->light.name,
			"\",", NULL);
	ft_putstr_fd(fd, "\n\t\t\"pos\" :\n\t\t{\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"x\" : ", ft_dtoa(light->light.pos.x), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_dtoa(light->light.pos.y), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\t\"z\" : ", ft_dtoa(light->light.pos.z), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t},\n\t\t\"color\" :\n\t\t{\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"r\" : ", ft_itoa((int)light->light.color.r),
			",\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"g\" : ", ft_itoa((int)light->light.color.g),
			",\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)light->light.color.b),
			",\n", NULL);
	ft_putstr_fd(fd, "\t\t},\n\t},\n", NULL);
}

static void		save_cam(int fd, t_env *e)
{
	ft_putstr_fd(fd, "\t\"camera\" :\n\t{\n\t\t", NULL);
	ft_putstr_fd(fd, "\"pos\" :\n\t\t{\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"x\" : ", ft_dtoa(e->cam->eye.x), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"y\" : ", ft_dtoa(e->cam->eye.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(e->cam->eye.z), ",\n\t\t},\n", NULL);
	ft_putstr_fd(fd, "\t\t\"dir\" :\n\t\t{\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"x\" : ", ft_dtoa(e->cam->l_at.x), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"y\" : ", ft_dtoa(e->cam->l_at.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(e->cam->l_at.z), ",\n\t\t},\n", NULL);
	ft_putstr_fd(fd, "\t\t\"up\" :\n\t\t{\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"x\" : ", ft_dtoa(e->cam->up.x), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"y\" : ", ft_dtoa(e->cam->up.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(e->cam->up.z), ",\n\t\t},\n", NULL);
	ft_putstr_fd(fd, "\t\t\"fov\" : ", ft_dtoa(e->cam->fov), ",\n\t\t", NULL);
	ft_putstr_fd(fd, "\"dist\" : ", ft_dtoa(e->cam->dist), ",\n\t},\n", NULL);
}

int				save_light_and_cam(t_env *e, int fd, t_parse_light *light)
{
	if (light)
	{
		while (light)
		{
			save_light(light, fd);
			light = light->next;
		}
		save_cam(fd, e);
		ft_putstr_fd(fd, "\t\"image size\" : [", ft_itoa(e->mlx->w / e->anti_a),
				", ", NULL);
		ft_putstr_fd(fd, ft_itoa(e->mlx->h / e->anti_a), "]\n", NULL);
		return (1);
	}
	return (0);
}
