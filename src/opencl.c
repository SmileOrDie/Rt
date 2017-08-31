/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/30 14:44:35 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

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

static void	ft_init_opencl_2(t_opencl *cl, int i, int err)
{
	char	*namefile[5];
	char	*source[5];

	namefile[0] = "src_cl/rt_h.cl";
	namefile[1] = "src_cl/add_light.cl";
	namefile[2] = "src_cl/inter_object.cl";
	namefile[3] = "src_cl/angle_object.cl";
	namefile[4] = "src_cl/vector.cl";
	while (++i < 5)
		source[i] = ft_create_source(namefile[i]);
	cl->kernel_program = clCreateProgramWithSource(cl->context, 5, (
		const char **)source, 0, &err);
	err ? ft_error(KERNEL,
		ft_strjoin("clCreateProgramWithSource -> cl->kernel_program -> ",
			ft_itoa(err))) : 0;
	i = 0;
	while (i < 5)
		free(source[i++]);
}

void		ft_init_opencl(t_envg *e, t_opencl *cl)
{
	int		err;
	size_t	len;
	char	buffer[100000];

	err = clGetPlatformIDs(1, &cl->platform, NULL);
	err = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, &cl->device, 0);
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	ft_init_opencl_2(cl, -1, err);
	if ((err = clBuildProgram(cl->kernel_program, 0, NULL, NULL, NULL, NULL))
		!= CL_SUCCESS)
	{
		(err = clGetProgramBuildInfo(cl->kernel_program, cl->device,
			CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len)) ?
		ft_error(KERNEL, ft_strjoin(
		"clGetProgramBuildInfo -> cl->kernel_program -> ", ft_itoa(err))) : 0;
		ft_error("\n", buffer);
	}
	cl->kernel = clCreateKernel(cl->kernel_program, "ft_start_calc", &err);
	err ? ft_l_err(err, 8) : 0;
	e->cl_e->cl = cl;
}

void		init_cl_e(t_env *e, t_env_cl *cl)
{
	cl->lst = e->tab_light;
	cl->light = e->light;
	cl->l_obj = e->l_obj;
	cl->nb_obj = e->nb_obj;
	cl->nb_light = e->nb_light;
	if (!(cl->color_lst = (t_color2 *)malloc(sizeof(t_color2) *
		*(e->nb_obj_pix[0]))))
		ft_error(MALLOC, "init_cl_e");
}
