/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/03 11:58:15 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

char	*ft_create_source(char *file_name)
{
	int fd;
	unsigned int file_len;
	struct stat file_status;
	char *source;

	fd = open(file_name, O_RDONLY);
	fstat(fd, &file_status);
	file_len = file_status.st_size;
	source = (char *)malloc(sizeof(char) * (file_len + 1));
	read(fd, source, file_len);
	close(fd);
	source[file_len] = 0;
	return (source);
}

void	init_cl_e(t_env *e, t_env_cl *cl)
{
	cl->lst = e->tab_light;
	cl->light = e->light;
	cl->l_obj = e->l_obj;
	cl->nb_obj = e->nb_obj;
	cl->nb_light = e->nb_light;
	if (!(cl->color_lst = (t_color2 *)malloc(sizeof(t_color2) * *(e->nb_obj_pix[0]))))
		ft_error(MALLOC, "init_cl_e");
}

void	ft_init_opencl(t_envg *e, t_opencl *cl)
{
	int		err;
	char	*source[5];
	char	*namefile[5];
	int		i;
	size_t	len;
	char	buffer[100000];

	if (!(e->cl_e = (t_env_cl *)malloc(sizeof(t_env_cl))))
		ft_error(MALLOC, "opencl.c => void ft_init_opencl(...)");
	if (!(e->cl_e->cl = (t_opencl *)malloc(sizeof(t_opencl))))
		ft_error(MALLOC, "opencl.c => void ft_init_opencl(...)");
	err = clGetPlatformIDs(1, &cl->platform, NULL);
	err = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, &cl->device, NULL);
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	namefile[0] = "src_cl/rt_h.cl";
	namefile[1] = "src_cl/add_light.cl";
	namefile[2] = "src_cl/inter_object.cl";
	namefile[3] = "src_cl/angle_object.cl";
	namefile[4] = "src_cl/vector.cl";
	i = 0;
	while (i < 5)
	{
		source[i] = ft_create_source(namefile[i]);
		i++;
	}
	cl->kernel_program = clCreateProgramWithSource(cl->context, 5, (const char **)source, 0, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateProgramWithSource -> cl->kernel_program -> ", ft_itoa(err))) : 0;
	if ((err = clBuildProgram(cl->kernel_program, 0, NULL, NULL, NULL, NULL)) != CL_SUCCESS)
	{
		(err = clGetProgramBuildInfo(cl->kernel_program, cl->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len)) ? ft_error(KERNEL, ft_strjoin("clGetProgramBuildInfo -> cl->kernel_program -> ", ft_itoa(err))) : 0;
		ft_putendl_fd(buffer, 2);
		exit(1);
	}
	e->cl_e->cl = cl;
	i = 0;
	while (i < 5)
	{
		free(source[i]);
		i++;
	}
}

void	ft_launch_calc(t_env *e, t_opencl *cl)
{
	size_t	global[1];
	int		err;

	init_cl_e(e, e->cl_e);
	cl->kernel = clCreateKernel(cl->kernel_program, "ft_start_calc", &err);
	err ? ft_error(KERNEL,
		ft_strjoin("clCreateKernel -> cl->kernel ", ft_itoa(err))) : 0;
	cl->obj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * e->nb_obj, e->l_obj, &err);
	err ? ft_error(KERNEL,
		ft_strjoin("clCreateBuffer -> e->l_obj ", ft_itoa(err))) : 0;
	cl->light = NULL;
	if (e->nb_light > 0)
	{
		cl->light = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * e->nb_light, e->light, &err);
		err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->light -> ", ft_itoa(err))) : 0;
	}
	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_env_cl), e->cl_e, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e -> ", ft_itoa(err))) : 0;
	cl->lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_l_obj) * *(e->nb_obj_pix[0]), e->cl_e->lst, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->lst -> ", ft_itoa(err))) : 0;
	cl->color_lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->color_lst -> ", ft_itoa(err))) : 0;
	cl->texture = NULL;
	if (e->nb_tex > 0)
	{
		cl->texture = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_mlx) * e->nb_tex, e->texture, &err);
		err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->texture -> ", ft_itoa(err))) : 0;
	}
	(err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->texture)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), (void *)&cl->obj)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 1 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), (void *)&cl->light)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 2 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), (void *)&cl->env)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 3 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->color_lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 4 -> ", ft_itoa(err))) : 0;
	global[0] = *(e->nb_obj_pix[0]);
	(err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, global, 0, 0, 0, 0)) ? ft_error(KERNEL, ft_strjoin("clEnqueueNDRangeKernel", ft_itoa(err))) : 0;
	(err = clEnqueueReadBuffer(cl->command_queue, cl->color_lst, CL_TRUE, 0, sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, 0, NULL, NULL)) ? ft_error(KERNEL, ft_strjoin("clEnqueueReadBuffer", ft_itoa(err))) : 0;
	clReleaseMemObject(cl->obj);
	clReleaseMemObject(cl->light);
	clReleaseMemObject(cl->env);
	clReleaseMemObject(cl->color_lst);
}
