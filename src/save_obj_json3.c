/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_obj_json3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 17:54:56 by phmoulin          #+#    #+#             */
/*   Updated: 2017/08/04 13:48:10 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void		copy_plan(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"plane\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",\n",
			NULL);
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

void		copy_cylindre(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"cylinder\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",",
			NULL);
	ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_dtoa(obj.radius), ",\n", NULL);
	ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_dtoa(obj.angle), ",\n", NULL);
	copy_pos(obj, fd);
	ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_dtoa(obj.ind_refrac), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_dtoa(obj.ind_reflec), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_dtoa(obj.ind_transp), ",\n",
			NULL);
	ft_putstr_fd(fd, "\t\t\"negatif\" : ", ft_itoa(obj.negatif), ",\n",
			NULL);
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

void		copy_cone(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"cone\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",",
			NULL);
	ft_putstr_fd(fd, "\n\t\t\"angle\" : ", ft_dtoa(obj.angle), ",\n", NULL);
	ft_putstr_fd(fd, "\t\t\"radius\" : ", ft_itoa(obj.radius), ",\n", NULL);
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

void		copy_circle(t_obj obj, int fd, t_envg *e)
{
	ft_putstr_fd(fd, "\t\"circle\" :\n\t{\n\t\t\"name\": \"", obj.name, "\",",
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
	ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_itoa(obj.angle), ",\n\t\t", NULL);
	ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_dtoa(obj.dir.x),
			",\n", NULL);
	ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_dtoa(obj.dir.y), ",\n\t\t\t", NULL);
	ft_putstr_fd(fd, "\"z\" : ", ft_dtoa(obj.dir.z), "\n\t\t},\n", NULL);
	if (obj.id_texture > 0)
		ft_putstr_fd(fd, "\t\t\"texture\" : \"",
				e->path_tex[(int)obj.id_texture - 1], "\"", NULL);
	ft_putstr_fd(fd, "\n\t},\n", NULL);
}
