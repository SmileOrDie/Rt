/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_obj_json2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 17:51:47 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/04 14:00:56 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		copy_pos(t_obj obj, int fd)
{
	ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_dtoa(obj.pos.x),
			NULL);
	ft_putstr_fd(fd, ",\n\t\t\t\"y\" : ", ft_dtoa(obj.pos.y), ",\n\t", NULL);
	ft_putstr_fd(fd, "\t\t\"z\" : ", ft_dtoa(obj.pos.z), "\n\t\t},\n", NULL);
}

void		copy_rgb(t_obj obj, int fd)
{
	ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ",
			ft_itoa((int)obj.color.r),
			NULL);
	ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ", ft_itoa((int)obj.color.g), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj.color.b), "\n\t\t},",
			NULL);
}

void		copy_square(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"square\" :\n\t{\n\t\t\"name\": ", obj.name, ",",
			NULL);
	ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_dtoa(obj.radius), ",\n", NULL);
	copy_pos(obj, fd);
	ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_dtoa(obj.ind_refrac), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_dtoa(obj.ind_reflec), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_dtoa(obj.ind_transp), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"negatif\" : ", ft_itoa(obj.negatif), ",\n", NULL);
	copy_rgb(obj, fd);
	ft_putstr_fd(fd, "\n\t\t\"angle\" : ", ft_itoa(obj.angle), ",\n\t\t", NULL);
	ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_dtoa(obj.dir.x),
			",\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_dtoa(obj.dir.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(obj.dir.z), "\n\t\t},\n", NULL);
	if (obj.id_texture > 0)
		ft_putstr_fd(fd, "\t\t\"texture\" : \"",
				e->path_tex[(int)obj.id_texture - 1], "\"", NULL);
	ft_putstr_fd(fd, "\n\t},\n", NULL);
}

void		copy_cube(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"cube\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",",
			NULL);
	ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_dtoa(obj.radius), ",\n", NULL);
	ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_itoa(obj.angle), ",\n", NULL);
	copy_pos(obj, fd);
	ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_dtoa(obj.ind_refrac), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_dtoa(obj.ind_reflec), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_dtoa(obj.ind_transp), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"negatif\" : ", ft_itoa(obj.negatif), ",\n", NULL);
	copy_rgb(obj, fd);
	ft_putstr_fd(fd, "\n\t\t\"dir\" :\n\t\t{\n\t\t\t\"x\" : ",
		ft_dtoa(obj.dir.x), ",\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_dtoa(obj.dir.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(obj.dir.z), "\n\t\t},\n", NULL);
	if (obj.id_texture > 0)
		ft_putstr_fd(fd, "\t\t\"texture\" : \"",
				e->path_tex[(int)obj.id_texture - 1], "\"", NULL);
	ft_putstr_fd(fd, "\n\t},\n", NULL);
}

void		copy_sphere(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"sphere\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",",
			NULL);
	ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_dtoa(obj.radius), ",\n", NULL);
	copy_pos(obj, fd);
	ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_dtoa(obj.ind_refrac), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_dtoa(obj.ind_reflec), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_dtoa(obj.ind_transp), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"negatif\" : ", ft_itoa(obj.negatif), ",\n", NULL);
	copy_rgb(obj, fd);
	if (obj.id_texture > 0)
		ft_putstr_fd(fd, "\t\t\"texture\" : \"",
				e->path_tex[(int)obj.id_texture - 1], "\"", NULL);
	ft_putstr_fd(fd, "\n\t},\n", NULL);
}
