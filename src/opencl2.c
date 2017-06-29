/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:54:55 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 16:55:15 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

char		*ft_create_source(char *file_name)
{
	int				fd;
	unsigned int	file_len;
	struct stat		file_status;
	char			*source;

	fd = open(file_name, O_RDONLY);
	fstat(fd, &file_status);
	file_len = file_status.st_size;
	source = (char *)malloc(sizeof(char) * (file_len + 1));
	read(fd, source, file_len);
	close(fd);
	source[file_len] = 0;
	return (source);
}

void		init_cl_e(t_env *e, t_env_cl *cl)
{
	cl->lst = e->tab_light;
	cl->light = e->light;
	cl->l_obj = e->l_obj;
	cl->nb_obj = e->nb_obj;
	cl->nb_light = e->nb_light;
	if (!(cl->color_lst = (t_color2 *)malloc(sizeof(t_color2) * \
	*(e->nb_obj_pix[0]))))
		ft_error(MALLOC, "init_cl_e");
}

int			ft_init_opencl2(t_opencl *cl, char *namefile[5])
{
	int		err;

	err = clGetPlatformIDs(1, &cl->platform, NULL);
	err = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, \
		&cl->device, NULL);
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	namefile[0] = "src_cl/rt_h.cl";
	namefile[1] = "src_cl/add_light.cl";
	namefile[2] = "src_cl/inter_object.cl";
	namefile[3] = "src_cl/angle_object.cl";
	namefile[4] = "src_cl/vector.cl";
	return (err);
}

void		ft_init_opencl(t_env *e, t_opencl *cl)
{
	t_norme6	n;

	n.err = ft_init_opencl2(cl, n.namefile);
	n.i = -1;
	while (++n.i < 5)
		n.source[n.i] = ft_create_source(n.namefile[n.i]);
	cl->kernel_program = clCreateProgramWithSource(cl->context, 5, \
		(const char **)n.source, 0, &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateProgramWithSource -> \
	cl->kernel_program -> ", ft_itoa(n.err))) : 0;
	if ((n.err = clBuildProgram(cl->kernel_program, 0, NULL, NULL, NULL, NULL))\
	!= CL_SUCCESS)
	{
		(n.err = clGetProgramBuildInfo(cl->kernel_program, cl->device, \
			CL_PROGRAM_BUILD_LOG, sizeof(n.buffer), n.buffer, &n.len)) ? \
			ft_error(KERNEL, ft_strjoin("clGetProgramBuildInfo -> \
			cl->kernel_program -> ", ft_itoa(n.err))) : 0;
		ft_putendl_fd(n.buffer, 2);
		exit(1);
	}
	e->cl_e->cl = cl;
	n.i = -1;
	while (++n.i < 5)
		free(n.source[n.i]);
}
